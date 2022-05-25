#include "mqtt.h"
#include "wifi.h"
// objet pour la connexion
WiFiClient espClient;
// connexion MQTT
PubSubClient client(espClient);

String base_topic; // stocke le préfixe commun à chaque topic

void setup_mqtt(){
 // formation du base topic basé sur l'adresse MAC
  base_topic = "espGEII" ;
  String mac = WiFi.macAddress();
  Serial.print("#MAC :");
  Serial.println(mac);
  base_topic += String(mac[12]) + String(mac[13]) + String(mac[15]) + String(mac[16]) + "/";
  Serial.print("MQTT base topic :");
  Serial.println(base_topic);

  client.setServer(MQTT_SERVER_IP, MQTT_PORT); // configuration broker

  client.setCallback(callback);  // configuration callback
  
  connectMqtt(); // première connexion

  
}
void loop_mqtt(){
if (!client.connected()) {
    if(!connectMqtt()) // non. on tente de se connecter
    { 
      return ;  // plus rien à faire connexion échouée
    }
    
  }
    // gestion MQTT
  client.loop();

  
}
// connexion ou reconnexion au broker
// dès qu'on est connecté, on s'abonne au(x) topic(s) souhaité(s)
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
    // connecté.
    return 0 ;
  }
}
// cette fonction s'exécute lorsqu'un message MQTT est reçu :
// le topic est toujours une chaîne de caractères (terminée par '\0')
// la payload pas forcément, la longueur de la payload est dans length
void callback(char* topic, byte* payload, unsigned int length) {

}
