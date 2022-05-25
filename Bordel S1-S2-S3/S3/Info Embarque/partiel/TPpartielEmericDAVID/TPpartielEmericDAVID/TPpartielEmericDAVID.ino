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
#define NbEch 1

//-------------Déclaration des sous-programmes, la définition des sous programmes et à la fin ...
void interBP2();

//-------------Déclaration des variables globales
bool flagTransfert = 0, flagMesure = 0;
unsigned int numEchantillon = 0;
unsigned int mesures[NbEch]; // tableau des mesures

//-------------Programme SETUP lancé au démarrage

void setup() {
  Serial.begin(9600);
  // configuration des broches des boutons poussoirs
  pinMode(BP1, INPUT_PULLUP);
  pinMode(BP2, INPUT_PULLUP);
  // configuration convertisseur N/A
  analogReference(DEFAULT);
  pinMode(LIGHT, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED1, OUTPUT);
  // configuration interruption BP2
  attachInterrupt(digitalPinToInterrupt(BP2), interBP2, RISING);

  // préconfiguration Timer1 pour interruption toutes les 2ms
  pinMode(DOUT, OUTPUT);
  digitalWrite(Dout, 0);
  TCCR1A = 0;
  TCCR1B =
  TIMSK1 =1;
  TCNT1 =
  sei();
}

//-------------Programme LOOP lancé après le SETUP et en boucle

void loop() {





}

//-------------Définition des sous programmes
void interBP2() { // S/P interruption BP2
 static bool drapeau;
 



}

ISR(TIMER1_OVF_vect ) // Fct It sur débordement Timer1
{
  static bool etatDout;
  TCNT1=34286;
  etatDout=!etatDout;
  digitalWrite(Dout,etatDout);
  digitalWrite(Led2,etatDout);


}
