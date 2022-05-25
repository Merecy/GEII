#include "capteurs.h"
#include "leds.h"
#include <BH1750.h>
#include <Wire.h>

BH1750 lightMeter(0x23);

void setup_capteurs() {
  Serial.begin(115200);
  Wire.begin();
  lightMeter.begin();
}

float lux () {
  float x = lightMeter.readLightLevel();
  Serial.println(x);
  return x;
}
