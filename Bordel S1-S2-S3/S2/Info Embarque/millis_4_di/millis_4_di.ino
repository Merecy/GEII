#define Led1 A3
#define Led2 A2
bool etat1, etat2;
unsigned long previousMillis1 = 0, previousMillis2 = 0;

void setup() {
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis1 >= 250) {
    previousMillis1 = currentMillis;
    etat1=!etat1;
    digitalWrite(Led1,etat1);
  }
  if (currentMillis - previousMillis2 >= 500) {
    previousMillis2 = currentMillis;
    etat2=!etat2;
    digitalWrite(Led2,etat2);
  }
}
