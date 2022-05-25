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

//---------------------------------------------------------------
void loop() {
  char tang [20] = " ", roul [20] = " ", lac [20] = " ", VXc [20] = " ", VYc [20] = " ";
  int t = 0, r = 0, l = 0, VXi = 0, VYi = 0;
  // quelque chose est il arrivé ?

  if (radio.available()) {
    int pls = radio.getDynamicPayloadSize();
    if (pls >= 1 && pls < 32) {
      radio.read((void*)payload, pls);
      payload[pls] = 0;
      //Serial.println(payload);
      sscanf(payload, "%s %d %s %d %s %d %s %d %s %d", roul, &r, tang, &t, lac, &l,VXc,&VXi,VYc,&VYi);
  
      Serial.print("R=");
      Serial.println(r);

      Serial.print("T=");
      Serial.println(t);

      Serial.print("L=");
      Serial.println(l);

      Serial.print("VX=");
      Serial.println(VXi*0.01);

      Serial.print("VY=");
      Serial.println(VYi*0.01);

      Serial.println("");
      
     
      couleurRGB(r);
    }
  }

  delay(500);

}

void couleurRGB(int a)
{
  int R, G, B;
  R = map(a, -90, 0, 0, 255);
  G = map(a, -90, 0, 255, 0);
  B = map(a, 0, 90, 0, 255);

  if (a > 0) {
    R = map(a, 0, 90, 255, 0);
    G = 0;
  }

  if (a < 0) {
    B = 0;
  }

  analogWrite(LedR, R);
  analogWrite(LedG, G);
  analogWrite(LedB, B);
}
