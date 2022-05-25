void setup_wifi(void);
void callback(char*, byte*, unsigned int);

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define Button_Flash D3
#define MSG_BUFFER_SIZE  (50)

// connection au wifi de la salle plus IP de l'ESP
const char* ssid = "********";
const char* password = "*******";
const char* mqtt_server = "192.168.0.9";
char* message;
unsigned long lastMsg = 0;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(Button_Flash, INPUT_PULLUP);
  setup_wifi();
  Serial.println(WiFi.macAddress());
  client.setServer(mqtt_server, 1883); //conection au port 1883 qui est lié a MQTT
  client.setCallback(callback); //definition du nom de la fonction a executer en cas de reception
}

void loop() {
  if (!client.connected()) {
    reconnect();              // si non connecter tentative de reconnexion
  }
  client.loop();

  static String MACaddress = WiFi.macAddress();
  static String topic = "espGEII" + MACaddress.substring(12,14) + MACaddress.substring(15,17);

  unsigned long now = millis();
  if (now - lastMsg > 10) {
    lastMsg = now;
    static bool last_state;
    if (last_state != digitalRead(Button_Flash)) {
      if (digitalRead(Button_Flash) == LOW) {
        String message = "ON";
        Serial.println(topic);
        Serial.println("Publish message: ON");
        client.publish(topic.c_str(), message.c_str());
        client.publish("EmericLed1", message.c_str());
      }
      if (digitalRead(Button_Flash) == HIGH) {
        String message = "OFF";
        Serial.println(topic);
        Serial.println("Publish message: OFF");
        client.publish(topic.c_str(), message.c_str());
        client.publish("EmericLed1", message.c_str());
      }
      last_state = digitalRead(Button_Flash);
    }
  }
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

  if (spayload == "ON") {
    digitalWrite(BUILTIN_LED, LOW); // allume la LED si "ON" est recu
  }
  else {
    if (spayload == "OFF") {
      digitalWrite(BUILTIN_LED, HIGH); // éteint la LED si "OFF" est recu
    }
  }
}

void reconnect() {
  // tentative de reconnexion en boucle
  while (!client.connected()) {
    Serial.print("Tentative de reconnexion a MQTT ...");
    String clientId = "ESP8266Client-" ;
    clientId += String(random(0xffff), HEX); //creation d'un ID client aleatoire

    //tentative de reconnexion avec le nouveaux Id client
    if (client.connect(clientId.c_str())) {
      Serial.println("connecte");
      client.subscribe("espGEIIC0F5/humidity");
      client.subscribe("espGEIIC0F5/temperature");
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
