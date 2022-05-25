#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define IN1 4
#define IN2 2
#define ENA 3
#define IN3 5
#define IN4 7
#define ENB 6
#define Left 0
#define Right 1
#define Forw 1
#define Backw -1
#define Stop 0

#define CH1 13
#define CH2 12
#define CH3 11

int i = 0, th1, th2, th3, vitesse, dir;
void cmd_motor(int, int, int);
int contrain(int, int, int);


void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);

  lcd.begin();
  lcd.setCursor(2, 0);
  lcd.print("CH1");
  lcd.setCursor(7, 0);
  lcd.print("CH2");
  lcd.setCursor(12, 0);
  lcd.print("CH3");
}


void loop() {
  lcd.setCursor(2, 1);
  th1 = pulseIn(CH1, HIGH);
  lcd.print(th1); lcd.print("   ");

  lcd.setCursor(7, 1);
  th2 = pulseIn(CH2, HIGH);
  lcd.print(th2); lcd.print("   ");

  lcd.setCursor(12, 1);
  th3 = pulseIn(CH3, HIGH);
  lcd.print(th3); lcd.print("   ");

  vitesse = (th2 - 1500) / 5;
  dir = (th1 - 1500) / 6;

  if (th3 > 1500)
  {
    if (vitesse > 0)
    {
      cmd_motor(Right, Forw, contrain(vitesse - dir, 100, 0));
      cmd_motor(Left, Forw, contrain(vitesse + dir, 100, 0));
    }
    else
    {
      vitesse = -vitesse;
      cmd_motor(Right, Backw, contrain(vitesse + dir, 80, 0));
      cmd_motor(Left, Backw, contrain(vitesse - dir, 80, 0));
    }
  }
  else
  {

  }
}





int contrain(int val, int maxi, int mini)
{
  if (val > maxi)
    val = maxi;
  else if (val < mini)
  {
    val = mini;
  }
  return val;

}


void cmd_motor(int motor, int direct, int power) {
  power = power;

  if (motor == Right)
  {
    if (direct == Forw)
    {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    }
    if (direct == Backw)
    {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
    }
    if (direct == Stop)
    {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
    }
    analogWrite(ENA, power * 2.55);
  }
  if (motor == Left)
  {
    if (direct == Forw)
    {
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
    if (direct == Backw)
    {
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }
    if (direct == Stop)
    {
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
    }
    analogWrite(ENB, power * 2.55);
  }
}
