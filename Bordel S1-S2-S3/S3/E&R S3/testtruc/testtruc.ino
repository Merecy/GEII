//https://randomnerdtutorials.com/esp32-lora-sensor-web-server/
//https://randomnerdtutorials.com/install-esp32-filesystem-uploader-arduino-ide/

//Pour le LoRa
#include <SPI.h>
#include <LoRa.h>

//Pour le Wifi
#include <WiFi.h>
#include <SPIFFS.h>
#include "ESPAsyncWebServer.h"

//Pour le serveur
#include <ESPmDNS.h>
//#include <NTPClient.h>
//#include <WiFiUdp.h>


#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISO
#define MOSI    27   // GPIO27 -- SX1278's MOSI
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     14   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND    868E6

const char* ssid     = "GEWIFITP1";
const char* password = "geiigeii";

String valeur[30];
String rssiV;
String Error = "-1";
String water = "0";


AsyncWebServer server(80);


void connectWiFi() {
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);

  while (!Serial);
  Serial.println();
  Serial.println("LoRa Receiver Callback");
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DI0);
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.receive();
  Serial.println("init ok");

  connectWiFi();

  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  if(!MDNS.begin("eau")){
    Serial.println("Error setting up MDNS responder");
  }

  MDNS.addService("http","tcp",80);
  
  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html");
  });
  
  server.on("/water", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", water);
  });
  
  server.on("/rssi", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", rssiV);
  });
  
//  server.on("/eau", HTTP_GET, [](AsyncWebServerRequest * request) {
//    request->send(SPIFFS, "/eau.jpg", "image/jpg");
//  });

  server.on("/icon", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/favicon.ico", "image/x-icon");
  });
  
  //Error 404
  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404, "text/plain", "Error 404, the content you are looking for was not found.");
  });
  
  // Start server
  server.begin();
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Read packet
    while (LoRa.available()) {
      String LoRaData = LoRa.readString();
      water = LoRaData;
      Serial.println(water);
    }
    rssiV = LoRa.packetRssi();
  }
}
