bool etat1, etat2;
unsigned long previousMillis1 = 0, previousMillis2 = 0;

void setup() {
bitSet(DDRC,3);
bitSet(DDRC,2);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis1 >= 250) {
    previousMillis1 = currentMillis;
    etat1=!etat1;
    bitWrite(PORTC,3,etat1);
  }
  if (currentMillis - previousMillis2 >= 500) {
    previousMillis2 = currentMillis;
    etat2=!etat2;
    bitWrite(PORTC,2,etat2);
  }
}
