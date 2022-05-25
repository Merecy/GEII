#include "mqtt.h"
#include "leds.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "GEWIFITP1";
const char* password = "geiigeii";
const char* mqtt_server = "192.168.0.9";
char* message;
unsigned long lastMsg = 0;
int x = 0;
static String MACaddress = WiFi.macAddress();
static String entete = "espGEII" + MACaddress.substring(12, 14) + MACaddress.substring(15, 17);

WiFiClient espClient;
PubSubClient client(espClient);

void setup_mqtt() {
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(Button_Flash, INPUT_PULLUP);
  setup_wifi();
  Serial.println(WiFi.macAddress());
  client.setServer(mqtt_server, 1883); //conection au port 1883 qui est lié a MQTT
  client.setCallback(callback); //definition du nom de la fonction a executer en cas de reception

}

void loop_mqtt() {
  String topic;
  if (!client.connected()) {
    reconnect();              // si non connecter tentative de reconnexion
  }
  client.loop();
}

void setup_wifi() {
  Serial.println();
  Serial.print("Connectinf to "); //affiche le nom de WiFi auquel nous nous connectons
  Serial.println(ssid);

  WiFi.mode(WIFI_STA); // definition du Wifi en mode statique
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) { // indique que le mode de WiFi n'est pas encore appliqué
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");  //affiche le topic depuis lequel le message arrive
  Serial.print(topic);
  Serial.print("] ");
  payload[length] = '\0'; //rajoute un caractère nul en fin de chaine pour qu'elle soit traiter en temps que chaine de caractere
  String spayload = (char*)payload; //convertie le payload en string
  String stopic = (char*)topic; //convertie le topic en string
  Serial.println(spayload); //affiche le message recu
  int numLED = (stopic.substring(17, 18)).toInt();
  traitementLed(numLED, spayload.toInt());
}

void reconnect() {
  String topic;
  // tentative de reconnexion en boucle
  while (!client.connected()) {
    Serial.print("Tentative de reconnexion a MQTT ...");
    String clientId = "ESP8266Client-" ;
    clientId += String(random(0xffff), HEX); //creation d'un ID client aleatoire

    //tentative de reconnexion avec le nouveaux Id client
    if (client.connect(clientId.c_str())) {
      Serial.println("connecte");
      for (int i = 0; i < 8; i++) {
        topic = entete + "/leds/" + i + "/rgb";
        //client.publish(topic.c_str(), "r,g,b"); //rgb
        client.subscribe(topic.c_str());
      }
      for (int i = 0; i < 8; i++) {
        topic = entete + "/leds/" + i + "/hsv";
        //client.publish(topic.c_str(), "h,s,v"); //hsv
        client.subscribe(topic.c_str());
      }
    }
    else {
      Serial.print("echec, rc=");

      Serial.print(client.state());
      Serial.println("reassayer dans 5 seconds");
      // attendre 5s entre chaque tentative
      delay(5000);
    }
  }
}
