#include <NTPClient.h>
#include <WiFi.h>


const char* ssid = "Honor 8X";
const char* password = "cookie83";

unsigned long lastTimetemps = 0;
unsigned long timerDelaytemps = 1000;

WiFiClient espClient;
WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

void setup() {
  Serial.begin(115200);
  Serial.println("");

  WiFi.begin(ssid, password);

  Serial.println("Connecting to WiFi.");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connected to the WiFi network");

  // Démarrage du client NTP - Start NTP client
  timeClient.begin();
}

void loop() {
  if ((millis() - lastTimetemps) > timerDelaytemps) {

    // Met à jour l'heure toutes les 10 secondes - update time every 10 secondes
    timeClient.update();
    Serial.println(timeClient.getFormattedTime());

    lastTimetemps = millis();
  }
}
