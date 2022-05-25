#include <SPI.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "printf.h"
#include <math.h>

#define RF24_CEPIN 9      // pin ce du spi
#define RF24_CSPIN 10      // pin cs du spi

RF24 radio(RF24_CEPIN, RF24_CSPIN);     //  le module
char payload[32 + 1] = {0};

const uint64_t txPipe = 0xE8E8E8E8E5LL; //Module d'emision
const uint64_t rxPipe = 0xF6F6F6F6F5LL; //5 c'est mon ID


unsigned long previousMillis = 0;
const long interval = 200;
#define X_out A0
#define Y_out A1
#define Z_out A2



void setup() {
  pinMode(X_out, INPUT);
  pinMode(Y_out, INPUT);
  pinMode(Z_out, INPUT);

  Serial.begin(9600);

  //                                      communication
  printf_begin();
  radio.begin();
  radio.printDetails();

  //                                 Default radio settings
  radio.enableDynamicPayloads();    // payload de taille variable
  radio.setDataRate(RF24_1MBPS);    // 1 Mbits/s
  radio.setPALevel(RF24_PA_MAX);    // puissance maxi
  radio.setChannel(0x2A);           // la fréquence 2,4G + n*1*M

  // delay 4 ms, 15 retries
  // 0 - 250us, 15 - 4000us
  radio.setRetries(15, 15);     // retrie & timeout

  radio.openWritingPipe(txPipe);
  radio.openReadingPipe(1, rxPipe);
  radio.setAutoAck(true);

  // en écoute
  radio.startListening();

  Serial.println("Si sa ne marche pas, go check CS et CE");
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    float VX = (analogRead(X_out) * 5.0) / 1023;
    float VY = (analogRead(Y_out) * 5.0) / 1023;
    float VZ = (analogRead(Z_out) * 5.0) / 1023;

    float GX = VX - 1.65;
    float GY = VY - 1.65;
    float GZ = VZ - 1.65;
    double G = sqrt(pow(GX, 2) + pow(GY, 2) + pow(GZ, 2));

    int Tangage = asin(GX / G) * (180 / PI);
    int Roulis = asin(GY / G) * (180 / PI);
    int Lacet = acos(GZ / G) * (180 / PI);


    //Serial.print("X=");
    //Serial.print(VX);
    //Serial.print(", Y=");
    //Serial.print(VY);
    //Serial.print(", Z=");
    //Serial.println(VZ);
    //Serial.print("Tangage= ");
    //Serial.print(Tangage);
    //Serial.print(", Roulis= ");
    //Serial.print(Roulis);
    //Serial.print(", Lacet= ");
    //Serial.println(Lacet);




    sprintf(payload,"Tang %d Roul %d Lac %d",Tangage,Roulis,Lacet);
    Serial.println(payload);


    // verify if channel is free
    if (!radio.testCarrier()) {
      // send payload
      radio.stopListening();    // en emission
      radio.write((void *)payload, strlen(payload));
      radio.startListening();
    }
    delay(500);


  }
}
