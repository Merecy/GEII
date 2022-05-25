//https://randomnerdtutorials.com/esp32-lora-sensor-web-server/
//https://randomnerdtutorials.com/install-esp32-filesystem-uploader-arduino-ide/
//https://randomnerdtutorials.com/esp32-thingspeak-publish-arduino/


//Note a faire pour la prohaine fois
//Faire un boutton cliquable html pour modif la periode de temps que l'on veut


//Pour le LoRa + donnee
#include <SPI.h>
#include <LoRa.h>

//Pour la gestion des donnees
#include <WiFi.h>
#include "ThingSpeak.h"

//Pour la gestion du serv
#include <SPIFFS.h>
#include "ESPAsyncWebServer.h"
#include <ESPmDNS.h>


#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISO
#define MOSI    27   // GPIO27 -- SX1278's MOSI
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     14   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND    868E6

WiFiClient  client;
const char* ssid = "Honor 8X";      //Nom du reseau
const char* password = "cookie83";  //Mot de Passe

unsigned long myChannelNumber = 3;                //Nombre de tableau qui existe au total
const char * myWriteAPIKey = "3SE7X1AB7L5NA2SA";  //Cle de l'API afin de pouvoir ecrire dessus

// Timer variables
unsigned long lastTime = 0;
unsigned long TimerDelay = 20000;

String rssiV;
String DonneeRecu;

float Debit = 0.0;
float LitreTotal = 0.0;
float LitreTotalAncient = 0.0;

int testx = 20, testy = 60;

void verif(int x);
void wifi();

AsyncWebServer server(80);

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

  WiFi.mode(WIFI_STA);
  Serial.println("Wifi check... Wait");
  wifi();

  ThingSpeak.begin(client);


  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  if (!MDNS.begin("eau")) {
    Serial.println("Error setting up MDNS responder");
  }

  MDNS.addService("http", "tcp", 80);

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html");
  });

  server.on("/winter", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/winter.jpg", "image/jpg");
  });

  //  server.on("/time",HTTP_GET, [](AsyncWebServerRequest * request) {
  //    request->send(SPIFFS,"text/plain",temps.getFormattedTime);
  //  });

  //  server.on("/eau", HTTP_GET, [](AsyncWebServerRequest * request) {
  //    request->send(SPIFFS, "/eau.jpg", "image/jpg");
  //  });
  //  server.on("/icon", HTTP_GET, [](AsyncWebServerRequest * request) {
  //    request->send(SPIFFS, "/favicon.ico", "image/x-icon");
  //  });

  //Error 404
  server.onNotFound([](AsyncWebServerRequest * request) {
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
      DonneeRecu = LoRa.readString();
      LitreTotal = DonneeRecu.toFloat();
      Serial.println(LitreTotal);
      Serial.println(Debit);
    }
  }

  if ((millis() - lastTime) > TimerDelay) {
    Debit = (float)(LitreTotal - LitreTotalAncient) / (TimerDelay / 1000);
    LitreTotalAncient = LitreTotal;
    wifi();
    testx = (testx + testy) / 2;
    testy = testy + 1;
    ThingSpeak.setField(1, LitreTotal);
    ThingSpeak.setField(2, LoRa.packetRssi());
    ThingSpeak.setField(3, Debit);
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    verif(x);
    lastTime = millis();
  }
}

void wifi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect");
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, password);
      delay(5000);
      Serial.print(".");
    }
    Serial.print("\nConnected on :");
    Serial.println(WiFi.localIP());
  }

}

void verif(int x) {
  if (x == 200) {
    Serial.println("Channel succefully updating.");
  }
  else {
    Serial.println("Problem updating water channel. HTTP error code " + String(x));
  }
}
