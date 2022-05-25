//https://randomnerdtutorials.com/esp32-lora-sensor-web-server/
//https://randomnerdtutorials.com/install-esp32-filesystem-uploader-arduino-ide/
//https://randomnerdtutorials.com/esp32-thingspeak-publish-arduino/

//Note a faire pour la prohaine fois
//Faire que les bouton change la valeur des tableau

//Pour le LoRa + donnee
#include <SPI.h>
#include <LoRa.h>

//Pour la gestion des donnees
#include <WiFi.h>
#include "ThingSpeak.h"

//Pour la gestion du serv
#include <SPIFFS.h>
#include "ESPAsyncWebServer.h"
#include <ESPmDNS.h>

#include <NTPClient.h>
#include <ESP_Mail_Client.h>

#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISO
#define MOSI    27   // GPIO27 -- SX1278's MOSI
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     14   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND    868E6

#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465
#define AUTHOR_EMAIL "serveurtcp08@gmail.com"
#define AUTHOR_PASSWORD "lemotdepasseduserveur"
#define RECIPIENT_EMAIL "luc.rastelo@gmail.com"


WiFiClient  client;
const char* ssid = "GEWIFITP1";      //Nom du reseau
const char* password = "geiigeii";  //Mot de Passe

unsigned long myChannelNumber = 3;                //Nombre de tableau qui existe au total
const char * myWriteAPIKey = "3SE7X1AB7L5NA2SA";  //Cle de l'API afin de pouvoir ecrire dessus

// Timer variables
unsigned long lastTime = 0;
unsigned long TimerDelay = 20000;

String rssiV;
String DonneeRecu;
String Messagetest = "no";

float Debit = 0.0;
float LitreTotal = 0.0;
float LitreTotalAncient = 0.0;

int testx = 20, testy = 60;

int heuremin = 2;
int heuremax = 5;

void verif(int x);
void wifi();
String normalisation(String date);


WiFiUDP ntpUDP;
NTPClient temps(ntpUDP, "fr.pool.ntp.org", 3600, 60000);

unsigned long Current_Time, Loop_Time;
int bouclesecu = 0;
void smtpCallback(SMTP_Status status);

AsyncWebServer server(80);

SMTPSession smtp;

void setup() {
  Serial.begin(115200);

  while (!Serial);
  Serial.println();
  Serial.println("LoRa Receiver Callback");
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DI0);
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.receive();
  Serial.println("init ok");

  WiFi.mode(WIFI_STA);
  Serial.println("Wifi check... Wait");
  wifi();

  ThingSpeak.begin(client);

  temps.begin();

  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  if (!MDNS.begin("eau")) {
    Serial.println("Error setting up MDNS responder");
  }

  MDNS.addService("http", "tcp", 80);

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html");
  });

  server.on("/winter", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/winter.jpg", "image/jpg");
  });

  //  server.on("/eau", HTTP_GET, [](AsyncWebServerRequest * request) {
  //    request->send(SPIFFS, "/eau.jpg", "image/jpg");
  //  });
  //  server.on("/icon", HTTP_GET, [](AsyncWebServerRequest * request) {
  //    request->send(SPIFFS, "/favicon.ico", "image/x-icon");
  //  });

  //Error 404
  server.onNotFound([](AsyncWebServerRequest * request) {
    request->send(404, "text/plain", "Error 404, the content you are looking for was not found.");
  });
  // Start server
  server.begin();
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Read packet
    while (LoRa.available()) {
      DonneeRecu = LoRa.readString();
      LitreTotal = DonneeRecu.toFloat();
      Serial.println(LitreTotal);
      Serial.println(Debit);
    }
  }

  if ((millis() - lastTime) > TimerDelay) {
    Debit = (float)(LitreTotal - LitreTotalAncient) / (TimerDelay / 1000);
    LitreTotalAncient = LitreTotal;
    wifi();
    testx = (testx + testy) / 2;
    testy = testy + 1;
    ThingSpeak.setField(1, LitreTotal);
    ThingSpeak.setField(2, LoRa.packetRssi());
    ThingSpeak.setField(3, Debit);
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    verif(x);
    Serial.print(Messagetest);
    prog_qui_envoie_le_mail();
    lastTime = millis();
  }
}

void wifi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect");
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, password);
      delay(5000);
      Serial.print(".");
    }
    Serial.print("\nConnected on :");
    Serial.println(WiFi.localIP());
  }

}

void verif(int x) {
  if (x == 200) {
    Serial.println("Channel succefully updating.");
  }
  else {
    Serial.println("Problem updating water channel. HTTP error code " + String(x));
  }
}

String normalisation(String date) {
  String years = "2020";
  String month = "01";
  String days = "01";
  String dateconver(years + "-" + month + "-" + days + "%2000:00:00");
  return (dateconver);
}


void prog_qui_envoie_le_mail()
{

  //avoir l'heure: temps.getHours()
  //avoir les minutes: temps.getMinutes()

  temps.update();
  if ((temps.getHours() == heuremin || temps.getHours() == heuremax)) {
    if (bouclesecu == 0) {
      if (Debit > 0) {

        smtp.debug(1);
        smtp.callback(smtpCallback);
        ESP_Mail_Session session;
        session.server.host_name = SMTP_HOST;
        session.server.port = SMTP_PORT;
        session.login.email = AUTHOR_EMAIL;
        session.login.password = AUTHOR_PASSWORD;
        session.login.user_domain = "";
        SMTP_Message message;
        message.sender.name = "ESP";
        message.sender.email = AUTHOR_EMAIL;
        message.subject = "ESP Test Email";
        message.addRecipient("Sara", RECIPIENT_EMAIL);
        String htmlMsg = "<div style=\"color:#2f4468;\"><h1>t'as une fuite mdr</h1><p>- Sent from ESP board</p></div>";
        message.html.content = htmlMsg.c_str();
        message.html.content = htmlMsg.c_str();
        message.text.charSet = "us-ascii";
        message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

        if (!smtp.connect(&session))
          return;

        if (!MailClient.sendMail(&smtp, &message))
          Serial.println("Error sending Email, " + smtp.errorReason());

        bouclesecu = 1;
      }
    }
  }

  if ((temps.getHours()<heuremin or temps.getHours()>heuremax)) {
    bouclesecu = 0;
  }
}


void smtpCallback(SMTP_Status status) {

  Serial.println(status.info());


  if (status.success()) {
    Serial.println("----------------");
    ESP_MAIL_PRINTF("Message sent success: %d\n", status.completedCount());
    ESP_MAIL_PRINTF("Message sent failled: %d\n", status.failedCount());
    Serial.println("----------------\n");
    struct tm dt;

    for (size_t i = 0; i < smtp.sendingResult.size(); i++) {

      SMTP_Result result = smtp.sendingResult.getItem(i);
      time_t ts = (time_t)result.timestamp;
      localtime_r(&ts, &dt);

      ESP_MAIL_PRINTF("Message No: %d\n", i + 1);
      ESP_MAIL_PRINTF("Status: %s\n", result.completed ? "success" : "failed");
      ESP_MAIL_PRINTF("Date/Time: %d/%d/%d %d:%d:%d\n", dt.tm_year + 1900, dt.tm_mon + 1, dt.tm_mday, dt.tm_hour, dt.tm_min, dt.tm_sec);
      ESP_MAIL_PRINTF("Recipient: %s\n", result.recipients);
      ESP_MAIL_PRINTF("Subject: %s\n", result.subject);
    }
    Serial.println("----------------\n");
  }
}
