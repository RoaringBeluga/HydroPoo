#include "EEPROM.h"

EEPROM::EEPROM()
{

}

EEPROM::EEPROM(uint8_t a)
{
  IIC_ADDR = a;
}

uint8_t i2c_EEPROM::readByte(const uint16_t address)
{
	uint8_t rdata = 0xFF;
  uint16_t addr = address % 4096;
	Wire.beginTransmission(IIC_ADDR);
	Wire.write((int)(addr >> 8)); // MSB
	Wire.write((int)(addr & 0xFF)); // LSB
	Wire.endTransmission();
	Wire.requestFrom((int)IIC_ADDR, 1);
	if (Wire.available()) {
		rdata = Wire.read();
	}
	return rdata;
}

void i2c_EEPROM::writeByte(const uint16_t address, const uint8_t data) {
    uint16_t addr = address % 4096;
    Wire.beginTransmission(IIC_ADDR);
		Wire.write((int)(addr >> 8)); // MSB
		Wire.write((int)(addr & 0xFF)); // LSB
		Wire.write(data);
		delay(5); // Little delay to assure EEPROM is able to process data; if missing and inside for look meses some values
		Wire.endTransmission();
}


uint8_t i2c_EEPROM::readB(const uint16_t address)
{
	return readByte(address);
}

int i2c_EEPROM::readW(const uint16_t address)
{
	return word(readByte(address), readByte(address+1));
}


void i2c_EEPROM::write(const uint16_t address, const uint8_t data) {
    writeByte(address, data);
}

void i2c_EEPROM::write(const uint16_t address, int data) {
    writeByte(address, highByte(data));
    writeByte(address+1, lowByte(data));
}
