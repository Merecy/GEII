#include <Wire.h>
#include <MechaQMC5883.h>
#include <math.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

MechaQMC5883 qmc;
int angle=0;
int x=0, y=0, z=0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  qmc.init();
  lcd.begin();
  lcd.setCursor(4, 0);
  lcd.print("angle :");
}

void loop() {
  qmc.read(&x, &y, &z);
  angle = atan2(x, y) * (180/PI);
  
  Serial.println(angle);
  lcd.setCursor(4, 1);
  lcd.print(angle);
  lcd.print("   ");


  delay(300);
}
