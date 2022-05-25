#include "Arduino.h"
String msg = "";
String number = "345";
String systemStatus = "heater:ON;fan:OFF" ;
int n = 12, p;
float x = 15.22458 , z;

void setup() {
  Serial.begin(9600);
  Serial.print("\n\n\n\n");
  msg = "n=" + String(n) + " x=" + String(x) + "\n";
  Serial.print(msg);
  msg = "n vaut " + String(n, BIN) + " en binaire et " + String(n,HEX) + " en hexa" + "\n";
  Serial.print(msg);
  p = number.toInt() + 1 ; // augmenter number de 1
  Serial.println(p);
  z = number.toInt() + 0.5 ; // augmenter number de 0.5
  msg = "z=" + String(z);
  Serial.println(msg);
  Serial.print("le chauffage est sur ");
  msg = systemStatus.substring(7, 9) + " le ventilateur est sur " + systemStatus.substring(14, 18); // utiliser la variable info
  Serial.print(msg);
  Serial.println(); // utiliser la variable info
}

void loop() {

}
