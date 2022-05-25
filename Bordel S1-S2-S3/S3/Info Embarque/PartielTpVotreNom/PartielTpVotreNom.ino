//-----------------------------------------------------------------------
//
//    DUT GEII TOULON Semestre 2 Info Embarquée
//
//    Partiel TP Grafcet et liaison série
//
//-----------------------------------------------------------------------
// Nom :DAVID                  Prénom :Emeric

//-------------Nom des différentes broches de l'arduino Nano
#define BP1 4
#define BP2 2
#define LED_R 5
#define LED_G 6
#define LED_B 10
#define LED2 A2
#define LED1 A3


//-------------Déclaration des sous-programmes, la définition des sous programmes et à la fin ...
void grafcet();
void gestionRGB(String ordre);

//-------------Déclaration des variables globales
int etape;
String inputString = "", commande = "";
bool flagSerie = false;


//-------------Programme SETUP lancé au démarrage
void setup() {
  // configurer les broches
  pinMode(BP1, INPUT_PULLUP);
  pinMode(BP2, INPUT_PULLUP);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED1, OUTPUT);
  inputString.reserve(200);
  // initialiser la liaison série
  Serial.begin(9600);
}

//-------------Programme LOOP lancé après le SETUP et en boucle

void loop() {
  // traiter les commandes reçues sur le port série
  if (flagSerie == true) {
    Serial.println(inputString);
    if (inputString.indexOf("RGB=") != -1)
    {
      gestionRGB(inputString);
    }
    else
    {
      commande = inputString;
    }
    
    inputString = "";
    flagSerie = false;
  }


  // traiter une étape du grafcet
  grafcet();

}

//-------------Définition des sous programmes
void grafcet() {
  switch (etape) {
    case 0:
      if ((digitalRead(BP1) == 0) or (commande.indexOf("Marche")!=-1))
      {
        Serial.println("Rotation broche");
        digitalWrite(LED1, HIGH);
        etape = 1;
        commande = "";
      }
      break;


    case 1:
      if ((digitalRead(BP2) == 0) or (commande.indexOf("Presence piece")!=-1))
      {
        Serial.println("Descente broche");
        digitalWrite(LED2, HIGH);
        etape = 2;
        commande = "";
      }
      break;


    case 2:
      if ((digitalRead(BP1) == 0) or (commande.indexOf("Broche basse")!=-1))
      {
        Serial.println("Monte broche");
        digitalWrite(LED2, LOW);
        etape = 3;
        commande = "";
      }
      break;

    case 3:
      if ((digitalRead(BP2) == 0) or (commande.indexOf("Broche haute")!=-1))
      {
        Serial.println("Attente ordre");
        digitalWrite(LED1, LOW);
        etape = 4;
        commande = "";
        Serial.println("Choix du cycle");
      }
      break;

    case 4:
      if (digitalRead(BP2) == 1)
      {
        if ((digitalRead(BP2) == 0) or (commande.indexOf("Presence piece")!=-1))
        {
          etape = 1;
          commande = "";
        }
        if ((digitalRead(BP1) == 0) or (commande.indexOf("Arret")!=-1))
        {
          etape = 5;
          commande = "";
          Serial.println("Arret");
        }
      }
      break;

    case 5:
      if (digitalRead(BP1) == 1)
      {
        etape = 0;
      }
      break;
  }
}

// accumuler les caractères reçus dans un variable de type String
// jusqu'à réception d'un '\n'
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();

    if (inChar == '\n') {
      flagSerie = true;
    }
    else {
      inputString += inChar;
    }
  }
}

// commander la led RGB en fonction de l'ordre reçu
void gestionRGB(String ordre) {
  if (ordre.indexOf("rouge") != -1) {
    analogWrite(LED_R, 50);
  }

  if (ordre.indexOf("vert") != -1) {
    analogWrite(LED_G, 50);
  }

  if (ordre.indexOf("bleu") != -1) {
    analogWrite(LED_B, 50);
  }

  if (ordre.indexOf("off") != -1) {
    analogWrite(LED_R, 0);
    analogWrite(LED_G, 0);
    analogWrite(LED_B, 0);
  }

}
