#include "Arduino.h"

String msg = "";
String number = "345";
String systemStatus = "heater:ON;fan:OFF" ;
int n = 12, p;
float x = 15.22458 , z;


void setup() {
  Serial.begin(9600);
  Serial.print("\n\n\n\n");
  msg = "n= " + String(n) + " x= " + String(x) + "\n";
  Serial.print(msg);
  msg = "n vaut " + String(n, BIN) + " en binaire, et en hexa n vaut " + String(n, HEX) + " \n";
  Serial.print(msg);
  p = number.toInt() + 1 ; // augmenter number de 1
  Serial.println(p);
  z = number.toFloat() + 0.5 ; // augmenter number de 0.5
  msg = "z=" + String(z);
  Serial.println(msg);
  Serial.print("le chauffage est sur ");
  msg = systemStatus.substring(7,9)+ " le ventilateur est " +systemStatus.substring(14,18);
  
  //  Serial.print("le chauffage est sur "+systemStatus.substring(9,10));
  //  if (systemStatus.substring(9,10) == "N")
  //    msg = "ON";
  //  else msg = "OFF";
  //  Serial.print(msg);
  //
  //  Serial.print(" le ventilateur est sur ");
  //  if (systemStatus.substring(18,19) == "F")
  //    msg = "OFF";
  //  else msg = "ON";
  
  Serial.print(msg);
  Serial.println(); // utiliser la variable info
}


void loop() {
}
