#include "capteurs.h"


void setup_capteurs() {
  Wire.begin();
  i2cWrite8(0x01); //ON
  i2cWrite8(0x07); //RESET
  i2cWrite8(0x10); //MODE HR

  delay(300);
}

void i2cWrite8(uint8_t data ){
  Wire.beginTransmission(capteur);
  Wire.write(data);
  Wire.endTransmission();
}

void loop_capteurs() {

}

uint16_t lumina(){
  int lux = 0;
  Wire.requestFrom(capteur, 2);
  while (!Wire.available());
  lux = Wire.read();
  while (!Wire.available());
  lux = (lux << 8) + Wire.read();
  return lux; 
}
