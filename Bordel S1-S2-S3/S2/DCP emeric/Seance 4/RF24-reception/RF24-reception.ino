#include <SPI.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "printf.h"
#include <stdio.h>

#define RF24_CEPIN 9			// pin ce du spi
#define RF24_CSPIN 10			// pin cs du spi

#define LedR 5
#define LedG 3
#define LedB 6

void couleurRGB(int);

RF24 radio(RF24_CEPIN, RF24_CSPIN);     //  le module
char payload[32 + 1] = {0};


const uint64_t rxPipe = 0xE8E8E8E8E5LL;  //Module de reception
const uint64_t txPipe = 0xF6F6F6F6F5LL;  //5 c'est mon ID


//---------------------------------------------------------------
void setup() {
  pinMode(LedR, OUTPUT);
  pinMode(LedG, OUTPUT);
  pinMode(LedB, OUTPUT);

  Serial.begin(9600);
  printf_begin();
  //                                      communication
  radio.begin();
  radio.printDetails();

  //                                 Regalge de la radio par defaut
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

  Serial.println("Si sa ne marche pas, go check CS et CE"); // Une ligne de code pour me rappeler de modifier CE et CS
}

//---------------------------------------------------------------
void loop() {
  int t = 0, r = 0, l = 0, VX = 0, VY = 0, VZ = 0;
  // quelque chose est il arrivé ?

  if (radio.available()) {
    int pls = radio.getDynamicPayloadSize();
    if (pls >= 1 && pls < 32) {
      radio.read((void*)payload, pls);
      payload[pls] = 0;
      Serial.print(payload); //Pour verifier qu'on recoit bien le payload

      //si on veut voir VX, VY, VZ
      //sscanf(payload, "R%dT%dL%dX%dY%dZ%d", &r, &t, &l, &VX, &VY, &VZ);


      //Pour verifier que le rouli, tangage ect.. marche bien
      sscanf(payload, "R%dT%dL%d", &r, &t, &l);

      //Serial.print("R=");
      //Serial.println(r);
      //
      //Serial.print("T=");
      //Serial.println(t);
      //
      //Serial.print("L=");
      //Serial.println(l);

      //Pour pouvoir afficher VX, VY et VZ en temps que float (du style 1.65)
      //
      //Serial.print("VX=");
      //Serial.println(VX*0.01);
      //
      //Serial.print("VY=");
      //Serial.println(VY*0.01);
      //
      //Serial.print("VZ=");
      //Serial.println(VZ*0.01);

      //Serial.println("");


      couleurRGB(r); // renvoie a une fonction s'ocupant de la rgb
    }
  }

  delay(500);

}

void couleurRGB(int a)
{
  int R, G, B;
  R = map(a, -90, 0, 255, 0);
  G = map(a, 0, 90, 0, 255);

  if (a > 0) {
    B = map(a, 0, 90, 255, 0);
    R = 0;
  }

  if (a < 0) {
    B = map(a, -90, 0, 0, 255);
    G = 0;
  }

  //Pour verifier la puissance des couleurs
  //Serial.println(R);
  //Serial.println(G);
  //Serial.println(B);

  analogWrite(LedR, R);
  analogWrite(LedG, G);
  analogWrite(LedB, B);
}
