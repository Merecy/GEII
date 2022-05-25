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

#define Infra A3

//#define DEBUG1
//#define DEBUG2
#define Course

int i = 0, th1, th2, th3, vitesse, dir, distd, distg, dista, tour, temps, pt = 0, j = 0, ordre, d = Forw, g = Forw , powerD = 0, powerG = 0;
void cmd_motor(int, int, int);
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

  digitalWrite(trigg, LOW);
  digitalWrite(trigd, LOW);

  //Serial.begin(9600);

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
}


void loop() {
  tour++;
  if (tour % 5 == 0)
  {
    th3 = pulseIn(CH3, HIGH);
  }

  if (th3 < 1500)
  {
    th1 = pulseIn(CH1, HIGH);
    th2 = pulseIn(CH2, HIGH);

    vitesse = (th2 - 1500) / 5;
    dir = (th1 - 1500) / 5;

    if (vitesse > 0)
    {
      d = Forw;
      g = Forw;
      powerD = constrain(vitesse - dir, 0, 100 );
      powerG =  constrain(vitesse + dir, 0, 100);
    }
    else
    {
      vitesse = -vitesse;
      d = Backw;
      g = Backw;
      powerD = constrain(vitesse + dir, 0, 80);
      powerG = constrain(vitesse - dir, 0, 80);
    }

    cmd_motor(Right, d, powerD);
    cmd_motor(Left, g, powerG);
  }


  else
  {
    temps = millis();
    if ((temps - pt) > 10)
    {
      j++;
      pt = temps;
      switch (j) {
        case 1 :
          distg = capteur(echog, trigg);

          break;

        case 2 :
          distd = capteur(echod, trigd);

          break;

        case 3 :
          dista = Dinfra();
          j = 0;

          break;
      }

      if ((dista <= 20) and (distd <= 20) and (distg <= 20))
      {
        powerD = 50;
        powerG = 50;
        d = Backw;
        g = Backw;
      }

      else if ((dista <= 20) and not(distd <= 20))
      {
        powerD = 70;
        powerG = 35;
        d = Backw;
        g = Backw;
      }

      else if ((dista <= 20) and not (distg <= 20))
      {
        powerD = 35;
        powerG = 70;
        d = Backw;
        g = Backw;
      }

      else if ((distd <= 20) and not (dista <= 20))
      {
        powerD = 35;
        powerG = 35;
        d = Forw;
        g = Backw;
      }

      else if ((distg <= 20) and not (dista <= 20))
      {
        powerD = 35;
        powerG = 35;
        d = Backw;
        g = Forw;
      }

      else
      {
        powerD = 35;
        powerG = 35;
        d = Forw;
        g = Forw;
      }
    }
    cmd_motor(Right, d, powerD);
    cmd_motor(Left, g, powerG);
    delay(20);
  }



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
