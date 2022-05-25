#ifndef WEBSERVER_H
#define WEBSERVER_H
#include <ESP8266WebServer.h>
void setup_webServer();
void loop_webServer();
void handleRoot();
void handleNotFound();
void handleOK();
void handleUP();
void handleCapt();
void handleLed();
void handleRGB();
#endif
