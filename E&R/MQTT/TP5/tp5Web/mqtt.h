#ifndef MQTT_H
#define MQTT_H
#include<PubSubClient.h>
#define MQTT_PORT 1883
#define MQTT_SERVER_IP "192.168.0.9"
void setup_mqtt();
void loop_mqtt();
int connectMqtt();
void callback(char* topic, byte* payload, unsigned int length); 
#endif
