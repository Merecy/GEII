#include <Wire.h>

#define capteur 0x23

void i2cWrite8( uint8_t address , uint8_t data );
uint16_t i2cRead16( uint8_t address );

unsigned long previousMillis = 0;
const long interval = 1000;

void setup()
{
  Wire.begin();// join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
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
  Wire.beginTransmission(address);
  Wire.write(0);
  uint16_t bits[15];
  int sto = Wire.endTransmission();
  if (sto < 0) return -1;

  const uint8_t length = 2;
  int bytes = Wire.requestFrom(address, length);
  if (bytes == 0) return -2;
  if (bytes < length) return -3;

  for (int i = 0; i < bytes; i++)
  {
    bits[i] = Wire.read();
  }
  return uint16_t(bits);
}
