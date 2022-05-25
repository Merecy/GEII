#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define echod A2
#define trigd 9
#define echog A1
#define trigg 10


long tempsg, tempsd;
int distg, distd;

void setup() {
  lcd.begin();
  pinMode(trigg, OUTPUT);
  pinMode(echog, INPUT);
  
  pinMode(trigd, OUTPUT);
  pinMode(echod, INPUT);
  
  digitalWrite(trigg, LOW);
  digitalWrite(trigd, LOW);
}

void loop() {
  digitalWrite(trigg, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigg, LOW);
  
  tempsg = pulseIn(echog, HIGH, 5882);

  digitalWrite(trigd, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigd, LOW);

  tempsd=pulseIn(echod,HIGH,5882);

  
  distg = tempsg * 0.034 / 2;
  distd = tempsd * 0.034 / 2;
  
  if (distg == 0)
  {
    distg = 100;
  }

  if (distd == 0)
  {
    distd = 100;
  }

  lcd.setCursor(0, 0);
  lcd.print("Dist g: ");
  lcd.print(distg);
  lcd.println(" cm    ");
  
  lcd.setCursor(0, 1);
  lcd.print("Dist d: ");
  lcd.print(distd);
  lcd.println(" cm    ");
  delay(40);
}
