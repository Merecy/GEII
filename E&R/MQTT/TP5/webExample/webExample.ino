#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char *ssid = "GEWIFITP1";
const char *password = "geiigeii";

void handleRoot() ;
void handleNotFound();

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("webExample.local")) {
    Serial.println("MDNS responder started");
  }
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {

  server.handleClient();
  MDNS.update();
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

//with raw string it is possible to place html 
// inside c++ code without escaping 
const char INDEX_HTML[] PROGMEM = R"=====(
<html>
 <b> Uptime is = %ld milliseconds </b>
</html>
)=====";



void handleRoot() {
 char temp[400]; // >= total size of the webpage to be served.
 snprintf(temp, 400, INDEX_HTML,millis());
 server.send(200, "text/html", temp);

}
