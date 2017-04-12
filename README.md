# Simple Deep-water culture hydroponic controller based on Arduino Nano

This controller was started as a hobby project to grow some fresh herbs for my kitchen. For now planned features are:

1. Control channels
    1. Air pump control (running for 20 minutes every hour by default).
    1. Water pump control. To simplify things the pump runs for 1 minute every hour and to prevent spilling the pump is wired in series with a simple float switch which will allow it to run only if the water level is too low. Should the water/nutrient tank be empty, water pump would just work as an additional air pump.
    1. Grow light control. Grow lights will be switched on based on the luxmeter reading
    1. Heater control. Heating pad (the kind they use on car seats) is planned to be installed and will be switched on and off based on the nutrient liquid temperature.
2. Sensors and other peripherial devices
    1. Nutrient temperature sensor(s): Waterproof DS18B20 probe(s).
    1. Ambient light sensor: BH1750 IIC sensor.
    1. Ambient temperature/humidity: DHT22, planned replacement with several of the AM23xx IIC sensors.
    1. RTC module: DS3201. Used to trigger pump ON/OFF commands and for general timekeeping (for future logger extension).
    1. External EEPROM: AT25C32 (on the RTC module). Will be used to store some settings?..
    1. Display: 2004 LCD on the IIC bus.
3. Planned extensions
    1. SD card data logger (SPI interface).
    1. Addition of a wireless controller (ESP8266) and MQTT integration. Will need to devise some way to interface with the Arduino.
    1. pH measurement (possibly – depends on whether pH probe can be acquired for a reasonable sum).
    1. Adding an enclosure with a fan for moisture/temperature control.

First version of hardware/software (simplified – only two pumps, no sensors, no display/logger, etc.) deployed on April 12th 2017 for unattended test run of about 10 days.

The project is licensed under [Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0) license](LICENSE)
