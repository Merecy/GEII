// https://randomnerdtutorials.com/esp32-thingspeak-publish-arduino/

//Pour le LoRa
#include <WiFi.h>
#include "ThingSpeak.h"

const char* ssid = "GEWIFITP1";   // your network SSID (name) 
const char* password = "geiigeii";   // your network password

WiFiClient  client;

unsigned long myChannelNumber = 2;
const char * myWriteAPIKey = "3SE7X1AB7L5NA2SA";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

int i=0;

void setup() {
  Serial.begin(115200);  //Initialize serial
  
  WiFi.mode(WIFI_STA);   
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);
        Serial.print(".");     
      } 
      Serial.print("\nConnected on :");
      Serial.println(WiFi.localIP());
    }

    
    i++;
    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    int x = ThingSpeak.writeField(myChannelNumber, 1, i, myWriteAPIKey);
    //uncomment if you want to get temperature in Fahrenheit
    //int x = ThingSpeak.writeField(myChannelNumber, 1, temperatureF, myWriteAPIKey);

    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    lastTime = millis();
  }
}
