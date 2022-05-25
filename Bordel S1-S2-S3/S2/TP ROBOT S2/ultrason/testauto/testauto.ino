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

#define echog A1
#define trigg 10
#define echod A2
#define trigd 9

int i = 0, th1, th2, th3, vitesse, dir, distd, distg;
void cmd_motor(int, int, int);
int contrain(int, int, int);
int capteur(int, int);


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

  pinMode(echog, INPUT);
  pinMode(echod, INPUT);
  pinMode(trigg, OUTPUT);
  pinMode(trigd, OUTPUT);

  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("USD:");
  lcd.setCursor(0, 1);
  lcd.print("USG:");
  lcd.setCursor(12, 0);
  lcd.print("mode");

  digitalWrite(trigg, LOW);
  digitalWrite(trigd, LOW);
}


void loop() {
  th1 = pulseIn(CH1, HIGH);
  th2 = pulseIn(CH2, HIGH);
  th3 = pulseIn(CH3, HIGH);

  distg = capteur(echog, trigg);
  distd = capteur(echod, trigd);


  lcd.setCursor(6, 0);
  lcd.print(distd); lcd.print("   ");

  lcd.setCursor(6, 1);
  lcd.print(distg); lcd.print("   ");

  lcd.setCursor(12, 1);
  if (th3 < 1500)
  {
    lcd.print("manu");
  }
  else
  {
    lcd.print("auto");
  }

  vitesse = (th2 - 1500) / 5;
  dir = (th1 - 1500) / 5;

  if (th3 < 1500)
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

    if (distd < 20)
    {
      cmd_motor(Right, Forw, 35);
      cmd_motor(Left, Backw, 25);
    }
    else if (distg < 20)
    {
      cmd_motor(Right, Backw, 25);
      cmd_motor(Left, Forw, 35);
    }
    else
    {
      cmd_motor(Right, Forw, 45);
      cmd_motor(Left, Forw, 45);
    }

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
    analogWrite(ENA, power * 2.15);
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



int capteur(int echo, int trig)
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
