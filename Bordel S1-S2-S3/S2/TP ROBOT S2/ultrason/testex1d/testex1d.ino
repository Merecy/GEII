#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define echod A2
#define trigd 9

int distd;
int capteur(int, int);

void setup() {
  lcd.begin();
  
  pinMode(trigd, OUTPUT);
  pinMode(echod, INPUT);
  
  digitalWrite(trigd, LOW);
}

int capteur(int echo,int trig)
{
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


void loop() {
  
  distd=capteur(echod,trigd);
  
  lcd.setCursor(0, 1);
  lcd.print("Dist d: ");
  lcd.print(distd);
  lcd.println(" cm    ");
  delay(40);
}
