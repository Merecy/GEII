#define Led1 A3
#define BP1 4

bool  BS2 = 0, oBS2 = 0, etat = 0;

void setup() {
  pinMode(Led1, OUTPUT);
  pinMode(BP1, INPUT_PULLUP);
}

void loop() {

    BS2 = digitalRead(BP1);
    if ((BS2 == 0) & (oBS2 == 1))
    {
      etat = !etat;
      digitalWrite(Led1, etat);
    }
    oBS2 = BS2;
  }
