#include "wifi.h"

char * ssid = "GEWIFITP1";
char * passwd = "geiigeii";

void setup_wifi() {

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, passwd);


  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("#Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("#IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("#RSSI : ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
  
  String mac = WiFi.macAddress();
  Serial.print("#MAC :");
  Serial.println(mac);
  String mdns = "geii" + String(mac[12]) + String(mac[13]) + String(mac[15]) + String(mac[16]);
  Serial.print("#MDNS name : ");
  Serial.print(mdns);
  Serial.println(".local");
  if (MDNS.begin(mdns.c_str())) {
    Serial.println("#MDNS responder started");
  }

}
void loop_wifi() {
  MDNS.update();
  
}
