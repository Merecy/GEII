#define Led1 A3
#define BP1 4
#define BP2 2
#define Led2 A2

void setup() {
pinMode(Led1,OUTPUT);
bitWrite(DDRC,2,1);

pinMode(BP1,INPUT_PULLUP);
pinMode(BP2,INPUT_PULLUP);

}

void loop() {
if (digitalRead(BP1))
  {
    digitalWrite(Led1,LOW);
  }
  else
  {
    digitalWrite(Led1,HIGH);
  }

if (digitalRead(BP2))
  {
    bitWrite(PORTC,2,0);
  }
  else
  {
    bitWrite(PORTC,2,1);
  }
}
