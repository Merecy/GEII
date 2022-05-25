#include <IRremote.h>
#define Pin 8

IRrecv Mon_Cube(Pin);
decode_results Cube_Resultat;

void setup() {
  Serial.begin(9600);
  Mon_Cube.enableIRIn();
}

void loop() {
  if (Mon_Cube.decode(&Cube_Resultat)) {
    //Serial.println(Cube_Resultat.value);
    if(Cube_Resultat.value==16752735){
      Serial.println("Haut");
    }
    else if(Cube_Resultat.value==16728255){
      Serial.println("Bas");
    }
    else if(Cube_Resultat.value==16742535){
      Serial.println("Droite");
    }
    else if(Cube_Resultat.value==16732335){
      Serial.println("Gauche");
    }
    else if(Cube_Resultat.value==4294967295){
      //Serial.println("Appuie continue");
    }
    else{
      Serial.print("Code non reconnu : ");
      Serial.println(Cube_Resultat.value);
    }
    Mon_Cube.resume();
  }
}
