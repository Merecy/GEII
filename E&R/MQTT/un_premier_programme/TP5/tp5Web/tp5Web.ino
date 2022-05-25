#include "wifi.h"
#include "leds.h"
#include "capteurs.h"
#include "mqtt.h"
#include "webserver.h"

void setup() {
   Serial.begin(115200);
   setup_wifi();
   setup_leds();
   setup_capteurs();
   setup_mqtt();
   setup_webServer();
}

void loop() {
   loop_wifi();
   loop_leds();
   loop_capteurs();
   loop_mqtt();
   loop_webServer();
}
