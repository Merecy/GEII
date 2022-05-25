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
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "FS.h"


#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISO
#define MOSI    27   // GPIO27 -- SX1278's MOSI
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     14   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND    868E6

#define LOOP_DELAY        30 * 1000 // Fréquence d'actualisation
#define RESET_INITIAL_NTPTIME false // Permet de réinitialisé le temps initial


const char* ssid     = "Honor 8X";
const char* password = "cookie83";

String valeur[30];
String rssiV;
String Error = "-1";
String water = "-9";


AsyncWebServer server(80);

WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);
int lastEvent;
int start = millis();
long int _now = 0;


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

void resetInitialTime() {
  timeClient.forceUpdate();
  _now = timeClient.getEpochTime();
  saveLastEvent();
}

bool lastEventExist() {
  File f = SPIFFS.open("/lastEvent.txt", "r");
  if (!f) {
    return false;
  }
  return true;
}

bool loadLastEvent() {
  // Recharge le dernier horodatage depuis la zone SPIFFS | Reload last date/time from SPIFFS area
  File f = SPIFFS.open("/lastEvent.txt", "r");
  if (!f) {
    Serial.println("Failed to open file, force NTP");
    return false;
  }
  lastEvent = f.readStringUntil('n').toInt();
  return true;
}

bool saveLastEvent() {
  File f = SPIFFS.open("/lastEvent.txt", "w");
  if (!f) {
    Serial.println("file open failed");
    return false;
  }
  f.println(_now);
  f.close();
  return true;
}

long int calculateTimeSpent() {
  loadLastEvent();
  timeClient.forceUpdate();
  _now = timeClient.getEpochTime();
  int timeSpent = _now - lastEvent;
  Serial.print("Time spent since last update (s): "); Serial.println(timeSpent);
  return timeSpent;
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

// Démarrage du client NTP - Start NTP client
  timeClient.begin();
  if ( RESET_INITIAL_NTPTIME ) {
    resetInitialTime();
  }
  if ( !lastEventExist() ) {
     Serial.println("First Boot, store NTP time on SPIFFS area");
     saveLastEvent();
  } else {
    Serial.println("NTP time already stored on SPIFFS area");
    calculateTimeSpent(); 
  }

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

  // Démarrage du client NTP - Start NTP client
  timeClient.begin();

  if(!MDNS.begin("eau")){
    Serial.println("Error setting up MDNS responder");
  }
  MDNS.addService("http","tcp",80);
}

void loop() {
  timeClient.update();
  calculateTimeSpent();
  delay(LOOP_DELAY);

  
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Read packet
    while (LoRa.available()) {
      String LoRaData = LoRa.readString();
      water = LoRaData;
      
      timeClient.update();
      Serial.print(timeClient.getFormattedTime());
      Serial.print(" -> ");
      
      Serial.println(water);
    }
    rssiV = LoRa.packetRssi();
  }
}
