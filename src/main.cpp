#include <Arduino.h>

#include <Wire.h>
#include <BH1750.h>


#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include <Rtc3201.h>

#include "EEPROM.h"
#include "Config.h"

#define DHTPIN        3
#define DHTTYPE       DHT22

BH1750 lightMeter(ADDR_LUX);
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
Rtc3201<TwoWire> Rtc(Wire);
EEPROM rtcPROM(ADDR_EEPROM);

void printDateTime(const RtcDateTime& dt);

void setup(){

  Serial.begin(9600);

  lightMeter.begin(BH1750_CONTINUOUS_HIGH_RES_MODE);
  //Serial.println(F("BH1750 Test"));

  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature"));
  Serial.print  (F("Sensor:       ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:   ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:    ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:    ")); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  (F("Min Value:    ")); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  (F("Resolution:   ")); Serial.print(sensor.resolution); Serial.println(" *C");
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Humidity"));
  Serial.print  (F("Sensor:       ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:   ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:    ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:    ")); Serial.print(sensor.max_value); Serial.println("%");
  Serial.print  (F("Min Value:    ")); Serial.print(sensor.min_value); Serial.println("%");
  Serial.print  (F("Resolution:   ")); Serial.print(sensor.resolution); Serial.println("%");
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;

  Rtc.Begin();
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
      printDateTime(compiled);
      Serial.println();

      if (!Rtc.IsDateTimeValid())
      {
          // Common Cuases:
          //    1) first time you ran and the device wasn't running yet
          //    2) the battery on the device is low or even missing

          Serial.println(F("RTC lost confidence in the DateTime!"));

          // following line sets the RTC to the date & time this sketch was compiled
          // it will also reset the valid flag internally unless the Rtc device is
          // having an issue

          Rtc.SetDateTime(compiled);
      }

      if (!Rtc.GetIsRunning())
      {
          Serial.println(F("RTC was not actively running, starting now"));
          Rtc.SetIsRunning(true);
      }

      RtcDateTime now = Rtc.GetDateTime();
      if (now < compiled)
      {
          Serial.println(F("RTC is older than compile time!  (Updating DateTime)"));
          Rtc.SetDateTime(compiled);
      }
      else if (now > compiled)
      {
          Serial.println(F("RTC is newer than compile time. (this is expected)"));
      }
      else if (now == compiled)
      {
          Serial.println(F("RTC is the same as compile time! (not expected but all is fine)"));
      }

      // never assume the Rtc was last configured by you, so
      // just clear them to your needed state
      Rtc.SetSquareWavePin(DS1307SquareWaveOut_Low);

      //rtcPROM.write(0x00, 42);
}


void loop() {

  uint16_t lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(1000);


  delay(delayMS);
    // Get temperature event and print its value.
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
      Serial.println(F("Error reading temperature!"));
    }
    else {
      Serial.print(F("Temperature: "));
      Serial.print(event.temperature);
      Serial.println(F(" *C"));
    }
    // Get humidity event and print its value.
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
      Serial.println(F("Error reading humidity!"));
    }
    else {
      Serial.print(F("Humidity: "));
      Serial.print(event.relative_humidity);
      Serial.println("%");
    };
    if (!Rtc.IsDateTimeValid())
        {
            // Common Cuases:
            //    1) the battery on the device is low or even missing and the power line was disconnected
            Serial.println(F("RTC lost confidence in the DateTime!"));
        }

        RtcDateTime now = Rtc.GetDateTime();

        printDateTime(now);
        Serial.println();

        delay(10000); // ten seconds
        uint8_t c = rtcPROM.readB(0x00);
        Serial.println(c, OCT);
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring,
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.print(datestring);
}
