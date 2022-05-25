#include "leds.h"
#include "capteurs.h"
#include "mqtt.h"

void setup() {
  Serial.begin(115200);
  setup_leds();
  setup_capteurs();
  setup_mqtt();
}
void loop() {
  loop_leds();
  loop_capteurs();
  loop_mqtt();

}
