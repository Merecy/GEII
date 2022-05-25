#include <SPI.h>

#include <RF24_config.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "printf.h"

#define RF24_CEPIN 9			// pin ce du spi
#define RF24_CSPIN 10			// pin cs du spi

RF24 radio(RF24_CEPIN, RF24_CSPIN);     //  le module
char payload[32 + 1] = {0};


const uint64_t txPipe = 0xE8E8E8E8E5LL; //Module d'emision
const uint64_t rxPipe = 0xF6F6F6F6F5LL; //5 c'est mon ID


//---------------------------------------------------------------
void setup() {
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

//---------------------------------------------------------------
void loop() {

  int x = rand() % 1000;
  //                               formation du payload
  sprintf(payload, "%d", x);
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
