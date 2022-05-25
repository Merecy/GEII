#include <Wire.h>
#include <tmp75.h>

#define BP2 2
#define BP1 4
#define LED2 A2
#define LIGHT A1
#define ALERTE 3

#define T_LOW 29
#define T_HIGH 30

TMP75 mySensor;

bool etat = 0, drapeau = 0;

void Blink();
void Temp();

void setup() {
  Wire.begin();
  int error = mySensor.begin();
  if (error) {
    Serial.println("TMP75 not responding...");
    while (1);
  }
  mySensor.setHighLimit(T_HIGH);
  mySensor.setLowLimit(T_LOW);

  attachInterrupt(digitalPinToInterrupt(BP2), Blink, RISING);
  attachInterrupt(digitalPinToInterrupt(ALERTE), Temp, CHANGE);

  pinMode(BP2, INPUT_PULLUP);
  pinMode(BP1, INPUT_PULLUP);
  pinMode(LED2, OUTPUT);
  pinMode(ALERTE, INPUT);

  analogReference(DEFAULT);
  Serial.begin(57600);
}

void loop() {
  if (drapeau == 1) {
    Serial.print("ALERTE 524 : ");
    Serial.print(mySensor.readTemperature());
    Serial.println(" °C");
    Serial.println("");
    delay(500);
  }

}

void Temp()
{
  drapeau = !drapeau;
}

void Blink()
{
  if (analogRead(LIGHT) < 800) {
    etat = HIGH;
  }
  else {
    etat = LOW;
  }
  Serial.println(analogRead(LIGHT));
  digitalWrite(LED2, etat);
}
