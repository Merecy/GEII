#define Led1 A3
#define BP1 4
#define BP2 2

bool BS = 0, oBS = 0, BS2 = 0, oBS2 = 0, etat = 0, mode = 0;

void setup() {
  pinMode(Led1, OUTPUT);
  pinMode(BP1, INPUT_PULLUP);
  pinMode(BP2, INPUT_PULLUP);
}

void loop() {
  BS = digitalRead(BP2);
  if ((BS == 0) & (oBS == 1))
  {
    mode = !mode;
  }
  oBS = BS;
  if (mode == 0)
  {
    digitalWrite(Led1, !digitalRead(BP1));
  }
  else
  {
    BS2 = digitalRead(BP1);
    if ((BS2 == 0) & (oBS2 == 1))
    {
      etat = !etat;
      digitalWrite(Led1, etat);
    }
    oBS2 = BS2;
  }

}
