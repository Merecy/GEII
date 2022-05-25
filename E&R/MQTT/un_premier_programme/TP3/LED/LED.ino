#include "capteurs.h"
#include "leds.h"
#include "mqtt.h"

const long interval = 20;
unsigned long previousMillis = 0;

void setup() {
  setup_leds();
  setup_capteurs();
  setup_mqtt();
}

void loop() {
  loop_mqtt();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    ledun();
    //testhsv();
    //lumiere(lux());
   
  }
}
