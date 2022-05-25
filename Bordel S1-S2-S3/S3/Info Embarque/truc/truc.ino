#define LedD1 A3
#define LedD2 A2

void setup() {
pinMode(LedD1,OUTPUT);
pinMode(LedD2,OUTPUT);
}

void loop() {
digitalWrite(LedD1,HIGH);
digitalWrite(LedD2,HIGH);

delay(250);

digitalWrite(LedD2,LOW);

delay(250);

digitalWrite(LedD2,HIGH);

delay(250);

digitalWrite(LedD2,LOW);
digitalWrite(LedD1,LOW);

delay(250);

digitalWrite(LedD2,HIGH);

delay(250);

digitalWrite(LedD2,LOW);

delay(250);

}
