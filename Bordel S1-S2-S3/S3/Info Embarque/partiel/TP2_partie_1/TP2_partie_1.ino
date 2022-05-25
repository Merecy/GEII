//-----------------------------------------------------------------------
//
//    DUT GEII TOULON Semestre 2 Info Embarquée
//
//    Partiel TP fin S2
//
//-----------------------------------------------------------------------

//-------------Nom des différentes broches de l'arduino Nano carte E&R S2
#define BP1 4
#define BP2 2
#define DOUT 7
#define LIGHT A1
#define LED2 A2
#define LED1 A3
//-------------Nombre d'échantillons de mesure
#define NbEch 500

//-------------Déclaration des sous-programmes, la définition des sous programmes et à la fin ...
void interBP2();

//-------------Déclaration des variables globales
bool flagTransfert = 0, flagMesure = 0;
unsigned int numEchantillon = 0;
unsigned int mesures[NbEch]; // tableau des mesures

//-------------Programme SETUP lancé au démarrage

void setup() {
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LIGHT, OUTPUT);
  pinMode(DOUT, OUTPUT);
  digitalWrite(DOUT, 0);
  // configuration des broches des boutons poussoirs
  pinMode(BP1, INPUT_PULLUP);
  pinMode(BP2, INPUT_PULLUP);
  // configuration convertisseur N/A

  // configuration interruption BP2
  attachInterrupt(digitalPinToInterrupt(BP2), interBP2, FALLING);

  // préconfiguration Timer1 pour interruption toutes les 2ms


}

//-------------Programme LOOP lancé après le SETUP et en boucle

void loop() {
  if (flagMesure == 1) {
    delay(500)
    digitalWrite(LED2, LOW);
    flagMesure = 0;
  }




}

//-------------Définition des sous programmes
void interBP2() { // S/P interruption BP2
  digitalWrite(LED2, HIGH);
  flagMesure = 1;
}

//ISR(TIMER1_OVF_vect) // Fct It sur débordement Timer1
//{

//}
