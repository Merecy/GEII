bool etat1, etat2;
unsigned long previousMillis1 = 0, previousMillis2 = 0;

void setup() {
DDRC = DDRC | 0b00001000;
DDRC = DDRC | 0b00000100;
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis1 >= 250) {
    previousMillis1 = currentMillis;
    if (etat1=LOW);{
      PORTC=PORTC | 0b00001000;
      etat1=HIGH;}
    else {
      PORTC=PORTC & 0b111110111;
      etat1=LOW;
    }
  }
  }
  if (currentMillis - previousMillis2 >= 500) {
    previousMillis2 = currentMillis;
     if (etat2=LOW);{
      PORTC=PORTC | 0b00000100;
      etat2=HIGH;
    else {
      PORTC=PORTC & 0b111111011;
      etat2=LOW;
  }
}
  }
}
