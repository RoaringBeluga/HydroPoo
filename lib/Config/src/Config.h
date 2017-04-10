#ifndef DSU_CONFIG_H
#define DSU_CONFIG_H

/*
Pin definitions
*/
#define ALARM_PIN   2 // DS3201 alarm interupt
#define DHT_PIN     3 // DHT22 sensor connection
#define DS18B20_PIN 4 // OneWire DS18B20 sensor(s)

#define AIRPUMP_PIN   5 // Air pump relay control pin, relay 1 @4-relay board
#define WATERPUMP_PIN 6 // Water pump relay control pin, relay 2 @4-relay board
#define LIGHT_PIN     7 // Lighting relay control pin, relay 3
#define HEATER_PIN    8 // Heater pad relay control pin, relay 4

/*
Should not be needed as we're almost out of GPIOs...
The values are just some placeholders!

#define SDA_PIN 9 // Default is ADC4
#define SCL_PIN 10 // Default is ADC5
*/

/*
Some provisions for SD card logger...
*/
#define SD_MOSI 11
#define SD_MISO 12
#define SD_SCK  13
#define SD_CS   10

/*
Pump runtimes
*/
#define AIR_RUN   1200000 // 20 minutes in milliseconds
#define WATER_RUN 60000   // 1 minute in milliseconds

/*
IIC addresses
*/
#define ADDR_LCD    0x3F
#define ADDR_RTC    0x68
#define ADDR_EEPROM 0x57
#define ADDR_LUX    0x23

#endif
