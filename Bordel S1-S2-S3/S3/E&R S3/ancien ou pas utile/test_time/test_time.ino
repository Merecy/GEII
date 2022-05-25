#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "FS.h"

#define NB_TRYWIFI        10        // Nbr de tentatives de connexion au réseau WiFi - Number of try to connect to WiFi network
#define LOOP_DELAY        30 * 1000 // Fréquence d'actualisation | update frequency
#define RESET_INITIAL_NTPTIME false // Permet de réinitialisé le temps initial | Allows to reset initial NTP time
// Paramètres WiFi | WiFi settings
const char* ssid = "Honor 8X";
const char* password = "cookie83";

WiFiClient espClient;
WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

int lastEvent;
int start = millis();
long int _now = 0;

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

  SPIFFS.begin();

  WiFi.begin(ssid, password);

  Serial.println("Connecting to WiFi.");
  int _try = 0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("..");
    delay(500);
    _try++;
    if ( _try >= NB_TRYWIFI ) {
      Serial.println("Impossible to connect WiFi network, go to deep sleep");
    }
  }
  Serial.println("Connected to the WiFi network");

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
}

void loop() {
  timeClient.update();
  calculateTimeSpent();
  delay(LOOP_DELAY);
}
