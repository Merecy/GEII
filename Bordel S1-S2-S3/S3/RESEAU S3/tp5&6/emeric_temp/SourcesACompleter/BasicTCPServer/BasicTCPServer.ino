//  
//
//     


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define ledVie D0
#define RLY D6

#ifndef STASSID
#define STASSID "XXXXXXXX"      //your SSID
#define STAPSK  "XXXXXXXX"      //your password
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

LiquidCrystal_I2C lcd(0xXX, 16, 2);

WiFiServer server(XXXXXXXX);    //define the port here

//////////////////////////////// setup ////////////////////////////////////////
void setup(void) {
  //--------------------------- GPIO LCD SERIAL ------------------------------
  pinMode(ledVie, XXXXXXXX);  // Initialize the LED_BUILTIN pin as an output
  pinMode(RLY, XXXXXXXX);
  lcd.begin();
  lcd.backlight();
  Serial.begin(115200);
  lcd.setCursor(0,0);
  lcd.print("Try to connect");
  lcd.setCursor(0,1);
  lcd.print(STASSID);

 //----------------------- WIFI connexion ----------------------------------- 
  WiFi.mode(XXXXXXXX);
  WiFi.begin(XXXXXXXX, XXXXXXXX);
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
  Serial.println(XXXXXXXX);

  if (MDNS.begin("XXXXXXXX")) {                 //XXXXXXXX.local is the MDNS name
    Serial.println("MDNS responder started");
  }
  lcd.setCursor(0,0);
  lcd.print(WiFi.localIP()); lcd.print("   ");
  lcd.setCursor(0,1);
  lcd.print("server wait");
  server.begin();
}
char recept[18]="";
int i=0;
WiFiClient client;    
char c;

//////////////////////////// loop ///////////////////////////////////////
void loop(void) {
  digitalWrite(ledVie, HIGH); 
  delay(50);
 
  MDNS.update();
  if (!client.XXXXXXXX {            //client is connected?
      client = XXXXXXXX.XXXXXXXX;  //test if one client is available
      if (XXXXXXXX) 
          client.XXXXXXXX("\nEnter \"rly on\" or \"rly off\":\n"); //connexion established
  }
  else {                            //client is connected
     c = client.XXXXXXXX();             //read char one by one
     if(XXXXXXXX && XXXXXXXXXX && XXXXXX) {                          //c is not CR not LF and buffer is not overlow
       recept[i++] = c;                                                //put c in the string recept
      }
      else {
           recept[i]='XXXXXXXX;
           i=XXXXXXXX;
           client.XXXXXXXX;                                         //deconnect the client
           lcd.setCursor(0,0);
           String cmd = (String)recept;
           lcd.print("Last command:"); lcd.print("   ");
           lcd.setCursor(0,1);
           lcd.print(cmd); lcd.print("        ");
           if(XXXXXXXX == XXXXXXXX) digitalWrite(RLY, HIGH);           //command equals "rly on"?
            else if (XXXXXXXX == XXXXXXXX) digitalWrite(RLY, LOW);    //command equals "rly off"?
            }
      } 

  digitalWrite(ledVie, LOW); 
  delay(50);
 
  
}
