#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Wire.h>

const char *ssid = "GEWIFITP1";
const char *password = "geiigeii";

#define capteur 0x23
#define LED_ANT D4

uint16_t lumina();
void i2cWrite8(uint8_t data );
void handleRoot() ;
void handleNotFound();
void handleUptime();
void handleLux();

ESP8266WebServer server(80);

void setup() { 
  Wire.begin();
  i2cWrite8(0x01); //ON
  i2cWrite8(0x07); //RESET
  i2cWrite8(0x10);

  delay(300);
  
  pinMode(LED_ANT,OUTPUT);
  digitalWrite(LED_ANT,0);
  SPIFFS.begin(); // Start the SPI Flash Files System
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(LED_ANT,!digitalRead(LED_ANT));
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("webExample")) {
    Serial.println("MDNS responder started");
  }
  //server.on("/", handleRoot);
  server.on("/lux", handleLux);
  server.on("/setLed", handleLed);
  
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
  digitalWrite(LED_ANT,1);
} 

void loop() {

  server.handleClient();
  MDNS.update();
}


void handleNotFound() {

  // If the client requests any URI not listed in server.on()
  bool found = handleFileRead(server.uri()) ; // send it if it exists in SPIFFS
  if ( found ) {
      return ; // file found then end function
  }
  // if the URI is not found in SPIFFS send 404       
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
  
}

//with raw string it is possible to place html 
// inside c++ code without espacing 
const char INDEX_HTML[] PROGMEM = R"=====(
<html>
 <b> Uptime is = %ld milliseconds </b>
</html>
)=====";



void handleRoot() {
 char temp[400]; // >= total size of the webpage to be served.
 snprintf(temp, 400, INDEX_HTML,millis());
 server.send(200, "text/html", temp);

}


String getContentType(String filename) { // convert the file extension to the MIME type
  if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if ( filename.endsWith(".jpg")  or filename.endsWith(".JPG") \
         or filename.endsWith(".JPEG") or filename.endsWith(".jpeg") ) return "image/jpeg";
  return "text/plain";
}

bool handleFileRead(String path) { // send the right file to the client (if it exists)
  Serial.println("handleFileRead: " + path);
  if (path.endsWith("/")) path += "index.html";         // If a folder is requested, send the index file
  String contentType = getContentType(path);            // Get the MIME type
  if (SPIFFS.exists(path)) {                            // If the file exists
    File file = SPIFFS.open(path, "r");                 // Open it
    size_t sent = server.streamFile(file, contentType); // And send it to the client
    file.close();                                       // Then close the file again
    return true;
  }
  Serial.println("\tFile Not Found");
  return false;                                         // If the file doesn't exist, return false
}

uint16_t lumina(){
  int lux = 0;
  Wire.requestFrom(capteur, 2);
  while (!Wire.available());
  lux = Wire.read();
  while (!Wire.available());
  lux = (lux << 8) + Wire.read();
  return lux; 
}

void i2cWrite8(uint8_t data ){
  Wire.beginTransmission(capteur);
  Wire.write(data);
  Wire.endTransmission();
}

const char CAPTEUR_HTML[] PROGMEM = R"=====(
<html>%ld</b>
</html> )=====";

void handleLux() {
  char temp[400]; // >= total size of the webpage to be served.
  snprintf(temp, 400, CAPTEUR_HTML, lumina());
  server.send(200, "text/html", temp);
}


         
  
