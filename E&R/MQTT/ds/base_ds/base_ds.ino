#include "hardware.h"
#include "wifi.h"
#include "leds.h"
#include "mqtt.h"

void setup() {
   Serial.begin(115200);
   setup_wifi();
   setup_leds();
   setup_mqtt();
}

void loop() {
   loop_wifi();
   loop_leds();
   loop_mqtt();
}
