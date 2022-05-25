#ifndef MQTT_H
#define MQTT_H

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
void reconnect();
void setup_mqtt();
void loop_mqtt();
void setup_wifi();
void callback(char* topic, byte* payload, unsigned int length);

#endif

#define Button_Flash D3
#define MSG_BUFFER_SIZE  (50)
