#define Led1 A3
#define BP1 4
unsigned long previousMillis = 0, currentMillis = 0;
bool  BS2 = 0, oBS2 = 0, etat = 0;

void setup() {
  pinMode(Led1, OUTPUT);
  pinMode(BP1, INPUT_PULLUP);
}

void loop() {
  currentMillis = millis();


  BS2 = digitalRead(BP1);
  if (currentMillis - previousMillis >= 10) {
    previousMillis = currentMillis;
    if ((BS2 == 0) & (oBS2 == 1))
    {
      etat = !etat;
      digitalWrite(Led1, etat);
    }
    oBS2 = BS2;
  }
}
