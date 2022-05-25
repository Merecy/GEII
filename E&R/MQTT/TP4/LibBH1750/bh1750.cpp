#include "bh1750.h"

BH1750::BH1750() {

}

void BH1750::begin(void) {
  i2cWrite8(POWER_ON);
  i2cWrite8(RESET);//RESET
  i2cWrite8(CNT_HR);//MODE HR 
  delay(300);
}

uint16_t BH1750::getRawLight(void) {
  uint16_t RawLight = i2cRead16();
  return RawLight;
}


void BH1750::i2cWrite8( uint8_t data ) {
  Wire.beginTransmission(ADDR);
  Wire.write(data);
  Wire.endTransmission();
}

uint16_t BH1750::i2cRead16(void) {
  int lux = 0;
  Wire.requestFrom(ADDR, 2);
  while (!Wire.available());
  lux = Wire.read();
  while (!Wire.available());
  lux = (lux << 8) + Wire.read();
  return lux;
}
