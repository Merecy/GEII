#include "webserver.h"
#include "capteurs.h"
#include "leds.h"

ESP8266WebServer server(80);

void setup_webServer() {
  server.on("/", handleRoot);
  server.on("/ok", handleOK);
  server.on("/uptime", handleUP);
  server.on("/capteur", handleCapt);
  server.on("/led", handleLed);
  server.on("/commandeRGB", handleRGB);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop_webServer(void) {
  server.handleClient();
}

void handleRoot() {
  server.send(200, "text/plain", "Salut");
}


void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void handleOK() {
  server.send(200, "text/plain", "OKKKKKKKKKK sa marche");
}

const char INDEX_HTML[] PROGMEM = R"=====(
<html>
 <b> Uptime is = %ld milliseconds </b>
</html>
)=====";

void handleUP(){
 char temp[400]; // >= total size of the webpage to be served.
 snprintf(temp, 400, INDEX_HTML,millis());
 server.send(200, "text/html", temp);
}


const char CAPTEUR_HTML[] PROGMEM = R"=====(
<html><meta http-equiv="refresh" content="1"> <b>Le capteur de lumiere BH1750 vaut : %ld lux </b>
</html> )=====";

void handleCapt() {
  char temp[400]; // >= total size of the webpage to be served.
  snprintf(temp, 400, CAPTEUR_HTML, lumina());
  server.send(200, "text/html", temp);
}

void handleLed() {
  server.send(200, "text/plain", "URL possible : 192.168.0.20/led?state=on/off");
  if (server.method() == HTTP_GET) {
    for (uint8_t i = 0; i < server.args(); i++) {
      if (server.argName(i) == "state") {
        stateled(server.arg(i));
      }
    }
  }
}

void handleRGB() {
  server.send(200, "text/plain", "URL possible : 192.168.0.20/led?state=on/off");
  if (server.method() == HTTP_GET) {
    for (uint8_t i = 0; i < server.args(); i++) {
      if (server.argName(i) == "red") {
        int red = (server.arg(i)).toInt();
      }
      if (server.argName(i) == "green") {
        int green = (server.arg(i)).toInt();
      }
      if (server.argName(i) == "blue") {
        int blue = (server.arg(i)).toInt();
      }
      if (server.argName(i) == "state") {
        stateRGB(server.arg(i),red, green, blue);
      }


    }
  }
}
