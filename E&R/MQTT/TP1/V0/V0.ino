#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define Boutton D3

const char* ssid = "GEWIFITP1";
const char* password = "geiigeii";
const char* mqtt_server = "192.168.0.9"; // Adresse du serveur

WiFiClient espClient; //creation objet Wifi
PubSubClient client(espClient); //creation objet pubsub avec specifite de l'objet wifi
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE], msgmil[MSG_BUFFER_SIZE], msgddos[MSG_BUFFER_SIZE];
int value = 0, valuemil = 0;

bool LastStateButton = 0;
String MonESP = "";
int kc =0;

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(Boutton, INPUT_PULLUP);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback); // initialisation du callback
}

void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  String MAC = WiFi.macAddress();
  MonESP = "espGEII" + MAC.substring(12, 14) + MAC.substring(15, 17) + "/";
  Serial.println(MAC);
  Serial.println(MonESP);
}

void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = 0;
  String stopic = (char*)topic; // On transforme le topic en string
  String spayload = (char*)payload; // On transforme le payload en string

  Serial.print("Message arrived [");
  Serial.print(stopic);
  Serial.print("] -> ");
  Serial.println(spayload);


  if (stopic == (MonESP + "EmericLed1").c_str()) { //On regarde le topic
    if (spayload == "ON") {       //On regarde apres le contenu du message
      digitalWrite(BUILTIN_LED, LOW); //La led est a l'envers, (Note that LOW is the voltage level
      // but actually the LED is on; this is because it is active low on the ESP-01)
    }
    else if (spayload == "OFF") {
      digitalWrite(BUILTIN_LED, HIGH);
    }
  }
}

void reconnect() {
  while (!client.connected()) {   //Tourne en boucle le temps que le client n'est pas connecte sur le serv mqtt
    Serial.print("Tentative de connexion MQTT ...");
    String clientId = "Emeric-";               // Juste pour savoir que c'est moi
    clientId += String(random(0xffff), HEX);  // Random avec la seed de connexion au wifi
    if (client.connect(clientId.c_str())) {
      Serial.println("Connecte");        // Connexion reussi

      client.publish((MonESP + "EmericTest").c_str(), "Connexion reussi");  // Sous la forme  -> client.publish("<topic>","<message>");
      client.publish((MonESP + "EmericLed1").c_str(), "Connexion reussi");
      client.publish((MonESP + "Lemillion").c_str(), "First Message");
      client.subscribe((MonESP + "EmericLed1").c_str());
      //client.subscribe("/#");
    } else {
      Serial.print("echoue, rc="); // Connexion echoue
      Serial.print(client.state());
      Serial.println(". Nouvelle tentative dans 5 secondes"); // Dans 5sec sa repart
      delay(5000);
    }
  }
}


void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int StateButton = digitalRead(Boutton);

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, MSG_BUFFER_SIZE, "jsuis en vie #%ld", value); // Pour voir si notre truc marche bien
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish((MonESP + "EmericTest").c_str(), msg);
  }


  if (StateButton != LastStateButton) {
    if (StateButton == HIGH) {
      snprintf (msg, MSG_BUFFER_SIZE, "ON"); // Pour voir si notre truc marche bien
      Serial.print("Boutton --> ");
      Serial.println(msg);
      client.publish((MonESP + "EmericLed1").c_str(), msg);
    }
    else if (StateButton == LOW) {
      snprintf (msg, MSG_BUFFER_SIZE, "OFF"); // Pour voir si notre truc marche bien
      Serial.print("Boutton --> ");
      Serial.println(msg);
      client.publish((MonESP + "EmericLed1").c_str(), msg);
    }
    LastStateButton = StateButton;
  }

//  if (valuemil < 1000000) {
//    ++valuemil;
//    snprintf (msgmil, MSG_BUFFER_SIZE, "#%ld", valuemil);
//    client.publish((MonESP + "Lemillion").c_str(), msgmil);
//  }


}
