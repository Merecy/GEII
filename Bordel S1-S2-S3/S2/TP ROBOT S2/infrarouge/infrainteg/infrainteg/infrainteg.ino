#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

//#define DEBUG1
//#define DEBUG2
#define Course

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

#define Infra A0

int i = 0, th1, th2, th3, vitesse, dir, distd, distg, dista;
void cmd_motor(int, int, int);
int contrain(int, int, int);
int capteur(int, int);
int Dinfra ();


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

  pinMode(Infra, INPUT);
  
#ifdef DEBUG1
  lcd.begin();
  lcd.setCursor(2, 0);
  lcd.print("CH1");
  lcd.setCursor(7, 0);
  lcd.print("CH2");
  lcd.setCursor(12, 0);
  lcd.print("CH3");
#endif
  
#ifdef DEBUG2
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("USD:");
  lcd.setCursor(0, 1);
  lcd.print("USG:");
  lcd.setCursor(10, 0);
  lcd.print("infra:");
#endif

#ifdef Course
  lcd.begin();
  lcd.setCursor(3, 0);
  lcd.print("Sponso KFC");
#endif

  digitalWrite(trigg, LOW);
  digitalWrite(trigd, LOW);
}


void loop() {
  th1 = pulseIn(CH1, HIGH);
  th2 = pulseIn(CH2, HIGH);
  th3 = pulseIn(CH3, HIGH);

  distg = capteur(echog, trigg);
  distd = capteur(echod, trigd);
  dista = Dinfra();
  
#ifdef DEBUG1
  lcd.setCursor(2, 1);
  lcd.print(th1); 
  lcd.print("   ");

  lcd.setCursor(7, 1);
  lcd.print(th2); 
  lcd.print("   ");

  lcd.setCursor(12, 1);
  lcd.print(th3); 
  lcd.print("   ");
#endif
  
#ifdef DEBUG2
  lcd.setCursor(5, 0);
  lcd.print(distd);
  lcd.print("  ");

  lcd.setCursor(5, 1);
  lcd.print(distg);
  lcd.print("  ");

  lcd.setCursor(12, 1);
  lcd.print(dista);
  lcd.print("  ");
#endif

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
    if ((dista <= 20) and not (distd <= 20))
    {
      cmd_motor(Right, Backw, 50);
      cmd_motor(Left, Backw, 35);
      delay(50);
    }
    else if ((dista <= 20) and not (distg <= 20))
    {
      cmd_motor(Right, Backw, 35);
      cmd_motor(Left, Backw, 50);
      delay(50);
    }
    else if ((distd <= 20) and not (dista <= 20))
    {
      cmd_motor(Right, Forw, 35);
      cmd_motor(Left, Backw, 25);
      delay(50);
    }
    else if ((distg <= 20) and not (dista <= 20))
    {
      cmd_motor(Right, Backw, 25);
      cmd_motor(Left, Forw, 35);
      delay(50);
    }
    else
    {
      cmd_motor(Right, Forw, 35);
      cmd_motor(Left, Forw, 35);
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


int Dinfra () {
  int dist = analogRead(Infra);
  dist = 3030 * pow(dist, -0.819) - 10;
  delayMicroseconds(40);
  if (dist > 100) {
    dist = 100;
  }
  return dist;
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
