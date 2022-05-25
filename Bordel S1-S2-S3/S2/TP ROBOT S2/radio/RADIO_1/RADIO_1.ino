#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define CH1 10
#define CH2 9
#define CH3 8

int th1, th2,th3;

   
void setup()
{
  lcd.begin();
  lcd.setCursor(2,0);
  lcd.print("CH1");
  lcd.setCursor(7,0);
  lcd.print("CH2");
  lcd.setCursor(12,0);
  lcd.print("CH3");
  pinMode(CH1,INPUT);
  pinMode(CH2,INPUT);
  pinMode(CH3,INPUT);
}

void loop()
{
  lcd.setCursor(2,1);
  th1=pulseIn(CH1,HIGH);
  lcd.print(th1); lcd.print("   ");
  lcd.setCursor(7,1);
  th2=pulseIn(CH2,HIGH);
  lcd.print(th2);lcd.print("   ");
  lcd.setCursor(12,1);
  th3=pulseIn(CH3,HIGH);
  lcd.print(th3);lcd.print("   ");
}
