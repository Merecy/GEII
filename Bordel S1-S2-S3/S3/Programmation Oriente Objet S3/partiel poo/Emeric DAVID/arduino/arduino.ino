#include <Wire.h>
#define bouton1 2
#define bouton2 4


int val=20;
//Je ne sais plus comment utiliser le capteur, donc afin d'avoir des valeur, j'ai decide de passer par les 2 boutons.
//Et j'ai trouver en scannant les port I2C, que quelque chose se trouve sur 0x48.

void setup() {
Serial.begin(9600);
pinMode(bouton1, INPUT_PULLUP);
pinMode(bouton2, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(bouton1) == LOW) { // Si mon bouton 1 est presse, cela rajoute 1 a la valeur envoyer
    val=val+1;
    Serial.println(val);
    Serial.write(val);             
  } 

  if (digitalRead(bouton2) == LOW) { // Si mon bouton 2 est presse, cela enleve 1 a la valeur envoyer
    val=val-1;
    Serial.println(val);
    Serial.write(val);               
  } 
  delay(1000); 
}
