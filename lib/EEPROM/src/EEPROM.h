#ifndef DSU_EEPROM_H
#define DSU_EEPROM_H
/*

EEPOM library for DS3201 and AT25C32 modules
EEPROM is treated as a ring buffer of 4096 bytes, so if the address
is out of bounds (>4095) it will just wrap to the beginning.

*/

#include <Wire.h>
#include <Arduino.h>

class EEPROM
{
private:
  uint8_t IIC_ADDR = 0x57; // Default EEPROM IIC address on DS3201 modules
  uint8_t readByte(const uint16_t address); // read 1 byte from the address in the EEPROM
  void    writeByte(const uint16_t address, const uint8_t data); // write 1 byte to the given EEPROM address
public:
  EEPROM(); // init with default address
  EEPROM(uint8_t a); // init with an IIC address that's diferent from default

  void    write(const uint16_t address, const uint8_t data); // write 1 byte to the given EEPROM address
  void    write(const uint16_t address, const int data); // write an integer to the given EEPROM address

  uint8_t readB(const uint16_t address); // read 1 byte from the address in the EEPROM

  int     readW(const uint16_t address); // read an integer
};
#endif
