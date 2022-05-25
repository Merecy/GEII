#include <Arduino.h>
#ifndef MQTT_H
#define MQTT_H
void setup_mqtt();
void setup_wifi();
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
void loop_mqtt();
#endif
