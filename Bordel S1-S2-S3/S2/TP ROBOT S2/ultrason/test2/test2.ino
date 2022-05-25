#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);


#define echog A1
#define trigg 10

#define echod A2
#define trigd 9


int distd, distg;
int capteur(int, int);

void setup() {
  lcd.begin();
  
}

void loop() {

  distg = capteur(echog, trigg);

  lcd.setCursor(0, 0);
  lcd.print("Dist g: ");
  lcd.print(distg);
  lcd.println(" cm    ");
  delay(40);

  distd = capteur(echod, trigd);
  
  lcd.setCursor(0, 1);
  lcd.print("Dist d: ");
  lcd.print(distd);
  lcd.println(" cm    ");
  delay(40);
}



int capteur(int echo, int trig)
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(trig, LOW);

  
  digitalWrite(trig, HIGH);
  delayMicroseconds(15);
  digitalWrite(trig, LOW);

  int temps = pulseIn(echo, HIGH, 5882);
  int dist = temps * 0.034 / 2;

  if (dist == 0)
  {
    dist = 100;
  }

  return dist;
}
