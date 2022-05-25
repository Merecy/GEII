#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define Infra A0
int dista;
int Dinfra ();

void setup() {
  pinMode(Infra, INPUT);
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("dist:");
}

void loop() {
  dista=Dinfra();

  lcd.setCursor(6, 0);
  lcd.print(dista);
  lcd.print("    ");
}

int Dinfra (){
  int dist = analogRead(Infra);
  dist = 3030 * pow(dist, -0.819) - 10;
  delayMicroseconds(15);
  if (dist > 100) {
    dist = 100;
  }
  return dist;
}
