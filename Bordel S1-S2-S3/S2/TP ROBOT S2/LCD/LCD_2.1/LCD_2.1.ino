#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
int TEMPS=0;
unsigned long previousMillis = 0;
const long interval = 1000;




void setup()
{
  lcd.begin();
  lcd.setCursor(3,0);
  lcd.print("Groupe E!");
  lcd.setCursor(0,1);
  lcd.print("TEMPS :");
  
}

void loop()
{
  unsigned long currentMillis = millis();
  
  if (currentMillis-previousMillis >= interval)
  {
  previousMillis = currentMillis;
  lcd.setCursor(8,1);
  lcd.print(TEMPS);
  TEMPS=TEMPS+1;  
  }
}
