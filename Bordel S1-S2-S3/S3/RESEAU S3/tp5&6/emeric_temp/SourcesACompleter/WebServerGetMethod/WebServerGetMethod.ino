//  GET method whith argument relay=[on|off|tog]
//
//     Use: http://xxxx.local/?relay=[on|off|tog]


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define ledVie D0
#define cmdeRelay D5

#ifndef STASSID
#define STASSID "tp5&6"
#define STAPSK  "geii2021"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
bool stateTog = false, stateRelay;
unsigned int timeTog = 0, intervall = 500;

ESP8266WebServer server(80);
LiquidCrystal_I2C lcd(0x27, 16, 2);


/////////////////////////////// 200 OK //////////////////////////////////////////
void handleRoot() { 
  String message = "<html> <body> <center> <H1> <BR> <BR> Salut <BR> Relay ";

  if(server.argName(0) == "relay") {    //relay=[on|off|tog]
     if(server.arg(0) == "on") {
      stateRelay = HIGH;
      digitalWrite(cmdeRelay,HIGH);
      lcd.setCursor(0,1);
      lcd.print("Relay ON ");      
      }else {
          if (server.arg(0) == "off") {
            stateRelay = LOW;
            digitalWrite(cmdeRelay,LOW);
            lcd.setCursor(0,1);
            lcd.print("Relay OFF");
            }
            else {
              if (server.arg(0) == "tog") {
                stateRelay = HIGH;
                digitalWrite(cmdeRelay,stateRelay);
                lcd.setCursor(0,1);
                lcd.print("Relay TOG");
                stateTog = true;
                timeTog = millis();
              }
          }
      }
  }
      
  stateRelay = digitalRead(cmdeRelay);
  if(stateRelay) message += "ON "; else message +="OFF ";
  message += "</H1> <BR> <BR>If you want to change <BR> Use URL: http://luem.local/?relay=[on|off|tog]</center>  </body> </html>";
  server.send(200, "text/html",message); 
  }

/////////////////////////////////// Error 404 //////////////////////////////////
void handleNotFound() {
  String message = "<html> <body> <H1> <center> Error 404, you noobs ! </center> </H1> </body> </html>";
  server.send(404, "text/html",message);
}

//////////////////////////////// setup ////////////////////////////////////////
void setup(void) {
  //--------------------------- GPIO LCD SERIAL ------------------------------
  pinMode(ledVie, OUTPUT);  // Initialize the LED_BUILTIN pin as an output
  pinMode(cmdeRelay, OUTPUT);
  lcd.begin();
  lcd.backlight();
  Serial.begin(115200);
  lcd.setCursor(0,0);
  lcd.print("Try to connect");
  lcd.setCursor(0,1);
  lcd.print(STASSID);

 //----------------------- WIFI connexion ----------------------------------- 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  int i=0;
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    lcd.setCursor(10,1);
   
    switch(i%3) { case 0: lcd.print("|"); break;
                  case 1: lcd.print("/"); break;
                  case 2: lcd.print("-");
              } 
     i++;         
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("luem")) {
    Serial.println("MDNS responder started");
  }
 //--------------------- server configuratiuon -------------------------------
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

  //------------------- Relay init ----------------------------------------
  stateRelay = LOW;
  digitalWrite(cmdeRelay,LOW);
  lcd.setCursor(0,0);
  lcd.print("ESP WEB Server");
  lcd.setCursor(0,1);
  lcd.print("Relay OFF");
}

//////////////////////////// loop ///////////////////////////////////////
void loop(void) {
  digitalWrite(ledVie, HIGH); 
  delay(50);
  server.handleClient();
  MDNS.update();
  digitalWrite(ledVie, LOW); 
  delay(50);
  //------------- tog mode: just during intervall time ON ------------
  if(stateTog == 1) {
    if(millis() > timeTog + intervall) {
      stateTog = false;
      stateRelay = LOW;
      digitalWrite(cmdeRelay,stateRelay);
      lcd.setCursor(0,1);
      lcd.print("Relay OFF");
    }
  }
}
