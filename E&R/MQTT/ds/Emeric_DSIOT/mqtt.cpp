#include "mqtt.h"
#include "wifi.h"
#include "leds.h"
// objet pour la connexion
WiFiClient espClient;
// connexion MQTT
PubSubClient client(espClient);

#define BUILTIN_LED D4

#define Boutton D3
bool LastStateButton = 0;

String base_topic; // stocke le préfixe commun à chaque topic
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
unsigned long lastMsg1 = 0, lastMsg2 = 0;
int i = 0;


int nbled = NUM_LEDS;
String mod = "rgb";
int couleur = 0;


void setup_mqtt() {
  // formation du base topic basé sur l'adresse MAC
  base_topic = "espGEIIED_" ;
  String mac = WiFi.macAddress();
  Serial.print("#MAC :");
  Serial.println(mac);
  base_topic += String(mac[12]) + String(mac[13]) + String(mac[15]) + String(mac[16]) + "/";
  Serial.print("MQTT base topic :");
  Serial.println(base_topic);

  client.setServer(MQTT_SERVER_IP, MQTT_PORT); // configuration broker

  client.setCallback(callback);  // configuration callback

  connectMqtt(); // première connexion

  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(Boutton, INPUT_PULLUP);


}
void loop_mqtt() {
  int StateButton = digitalRead(Boutton);
  if (!client.connected()) {
    if (!connectMqtt()) // non. on tente de se connecter
    {
      return ;  // plus rien à faire connexion échouée
    }
  }
  // gestion MQTT
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg1 > 30000) {
    lastMsg1 = now;
    snprintf (msg, MSG_BUFFER_SIZE, "%ld", WiFi.RSSI());
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish((base_topic + "rssi").c_str(), msg);
  }

  if (now - lastMsg2 > 10) {
    lastMsg2 = now;
    if (StateButton != LastStateButton) {
      if (StateButton == LOW) {
        i++;
        snprintf (msg, MSG_BUFFER_SIZE, "ON%d", i); // Pour voir si notre truc marche bien
        Serial.print("Boutton --> ");
        Serial.println(msg);
        client.publish((base_topic + "btn").c_str(), msg);
      }
      LastStateButton = StateButton;
    }
  }
}

int connectMqtt() {
  // Connecté au broker ?
  if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESPGEIIClient-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    // non. On se connecte.
    if ( !client.connect(clientId.c_str()) ) {
      Serial.print("Erreur connexion MQTT, rc=");
      Serial.println(client.state());
      return -1; // on essayera à nouveau au prochain tour de boucle
    }
    Serial.println("Connexion serveur MQTT ok");
    client.publish((base_topic + "rssi").c_str(), "rssi?");
    client.publish((base_topic + "btn").c_str(), "ONx");
    client.publish((base_topic + "led").c_str(), "On ou OFF");
    client.publish((base_topic + "nbled").c_str(), "Nombre de led");
    client.publish((base_topic + "mode").c_str(), "rgb / hsv");
    client.publish((base_topic + "couleur").c_str(), "valeur rgb");


    client.publish((base_topic + "couleur").c_str(), "nleds,mode,v1,v2,v3");
    //client.subscribe("espGEIIC0F5/temperature");
    client.subscribe((base_topic + "led").c_str());
    client.subscribe((base_topic + "nbled").c_str());
    client.subscribe((base_topic + "mode").c_str());
    client.subscribe((base_topic + "couleur").c_str());
    return 0 ;
  }
}
// cette fonction s'exécute lorsqu'un message MQTT est reçu :
// le topic est toujours une chaîne de caractères (terminée par '\0')
// la payload pas forcément, la longueur de la payload est dans length
void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = 0;
  String stopic = (char*)topic; // On transforme le topic en string
  String spayload = (char*)payload; // On transforme le payload en string

  Serial.print("Message arrived [");
  Serial.print(stopic);
  Serial.print("] -> ");
  Serial.println(spayload);

  if (stopic == "espGEIIC0F5/temperature") {
    Serial.print("La temperature est de : ");
    Serial.println(spayload);
  }

  if (stopic == base_topic + "led") {
    if (spayload == "ON") {
      digitalWrite(BUILTIN_LED, LOW);
      led(8, "rgb", 5621021);
    }
    else if (spayload == "OFF") {
      digitalWrite(BUILTIN_LED, HIGH);
    }
  }

  if (stopic == base_topic + "nbled") {
    nbled = spayload.toInt();
    Serial.println(String("nbled : ") + nbled);
  }

  if (stopic == base_topic + "mode") {
    mod = spayload;
    Serial.println(String("mode : ") + mod);
  }

  if (stopic == base_topic + "couleur") {
    couleur = spayload.toInt();
    Serial.println(String("couleur : ") + couleur);
    led(nbled, mod, couleur);
  }




}
