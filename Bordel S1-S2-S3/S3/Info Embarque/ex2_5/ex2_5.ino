#define Led1 A3
#define BP1 4

void setup() {
pinMode(Led1,OUTPUT);
pinMode(BP1,INPUT_PULLUP);

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
}
