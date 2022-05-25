#include <Wire.h>

#define capteur 0x23

uint16_t i2cRead16( uint8_t address );
void i2cWrite8( uint8_t address , uint8_t data );

unsigned long previousMillis = 0;
const long interval = 500;

void setup()
{
  Serial.begin(9600);

  Wire.begin();
  i2cWrite8(capteur,0x01);//ON
  i2cWrite8(capteur,0x07);//RESET
  i2cWrite8(capteur,0x10);//MODE HR
  
  delay(300);
}

void i2cWrite8( uint8_t address , uint8_t data ){
  Wire.beginTransmission(address);
  Wire.write(data);
  Wire.endTransmission();
}

void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    Serial.println(i2cRead16(capteur));
  }
}




uint16_t i2cRead16( uint8_t address ) {
  int lux = 0;
  Wire.requestFrom(address, 2);
  while (!Wire.available());
  lux = Wire.read();
  while (!Wire.available());
  lux = (lux << 8) + Wire.read();
  return lux; 
}
