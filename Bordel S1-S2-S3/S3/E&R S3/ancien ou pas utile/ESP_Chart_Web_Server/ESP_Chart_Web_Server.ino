/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

// Import required libraries

  #include <WiFi.h>
  #include <ESPAsyncWebServer.h>
  #include <SPIFFS.h>




// Replace with your network credentials
const char* ssid = "GEWIFITP1";
const char* password = "geiigeii";

int i=0;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readBME280Temperature() {
  // Read temperature as Celsius (the default)
  float t = 45+i;

    Serial.println(t);
    return String(t);
 
}

String readBME280Humidity() {
  float h = 78+i;

    Serial.println(h);
    return String(h);
 
}

String readBME280Pressure() {
  float p = 1024+i;

    Serial.println(p);
    return String(p);
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  


  // Initialize SPIFFS
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readBME280Temperature().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readBME280Humidity().c_str());
  });
  server.on("/pressure", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readBME280Pressure().c_str());
  });

  // Start server
  server.begin();
}
 
void loop(){
  
  i++;
  
  
}
