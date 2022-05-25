#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define DEBUG


LiquidCrystal_I2C lcd(0x27, 16, 2);

int s=0;
int m=0;
int h=0;

unsigned long avant = 0;        
const long interval = 1000;    

void setup()
{
  lcd.begin();
  lcd.setCursor(5,0);
  lcd.print("TEMPS:");
  lcd.setCursor(6,1);
  lcd.print(":");
  lcd.setCursor(9,1);
  lcd.print(":");
  
}

void loop()
{

  unsigned long maintenant = millis();
 
  if(maintenant - avant >= interval) {

    avant = maintenant; 
    s=s+1;
    if(s<10){

       lcd.setCursor(11,1);
       #ifdef DEBUG
       lcd.print(s);
       #endif
       lcd.setCursor(10,1);
       lcd.print("0");
    }
    else{
       lcd.setCursor(10,1);
       #ifdef DEBUG
       lcd.print(s);
       #endif
    }
    if(m<10){
       lcd.setCursor(8,1);
       #ifdef DEBUG
       lcd.print(m);
       #endif
       lcd.setCursor(7,1);
       lcd.print("0");

    }
    else{
      lcd.setCursor(7,1);
      #ifdef DEBUG
      lcd.print(m);
      #endif
    }
    if(h<10){
       lcd.setCursor(5,1);
       #ifdef DEBUG
       lcd.print(h);
       #endif
       lcd.setCursor(4,1);
       lcd.print("0");
    }
    else{
       lcd.setCursor(4,1);
       #ifdef DEBUG
       lcd.print(h);
       #endif
    }
    if(s==59){
      s=-1;
      m=m+1;

      if(m==60){
        m=0;
        h=h+1;
        if(h==24){
          h=0;
        }
      }
    }
    
    
}
}
