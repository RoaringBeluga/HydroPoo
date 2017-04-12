#include <Arduino.h>

#include <avr/pgmspace.h>

#include <Wire.h>

#include <RtcDS3231.h>

#include "Config.h"

RtcDS3231<TwoWire> Rtc(Wire);

void printDateTime(const RtcDateTime& dt);

void setup(){

  Serial.begin(9600);

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
      Rtc.Enable32kHzPin(false);
      Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);

      pinMode(AIRPUMP_PIN, OUTPUT);digitalWrite(AIRPUMP_PIN, HIGH);
      pinMode(WATERPUMP_PIN, OUTPUT);digitalWrite(WATERPUMP_PIN, HIGH);

}


void loop() {


    if (!Rtc.IsDateTimeValid())
        {
            // Common Cuases:
            //    1) the battery on the device is low or even missing and the power line was disconnected
            Serial.println(F("RTC lost confidence in the DateTime!"));
        }

        RtcDateTime now = Rtc.GetDateTime();

        Serial.println();

        uint8_t nHour = now.Hour();
        uint8_t nMin  = now.Minute();
        if((nMin>=motorControl[nHour][0])&&(nMin<=motorControl[nHour][1]))
        {
          digitalWrite(AIRPUMP_PIN, LOW);
          Serial.print(F("Air pump turned on at: "));
          printDateTime(now);
          Serial.println();
        } else {
          digitalWrite(AIRPUMP_PIN, HIGH);
        };
        if((nMin>=motorControl[nHour][2])&&(nMin<=motorControl[nHour][3]))
        {
          digitalWrite(WATERPUMP_PIN, LOW);
          Serial.print(F("Water pump turned on at: "));
          printDateTime(now);
          Serial.println();
        } else {
          digitalWrite(WATERPUMP_PIN, HIGH);
        };
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
