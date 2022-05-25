#include <IRremote.h>
#include <Wire.h>
#define RECEIVER_PIN 8
#define LedR 5
#define LedG 6
#define LedB 10

IRrecv receiver(RECEIVER_PIN);
decode_results results;

void LedRGB(int R, int G, int B) {
  digitalWrite(LedR, R);
  digitalWrite(LedG, G);
  digitalWrite(LedB, B);
}


void setup()
{
  Serial.begin(9600);
  pinMode(LedR, OUTPUT);
  pinMode(LedG, OUTPUT);
  pinMode(LedB, OUTPUT);
  receiver.enableIRIn();

}
void loop()
{
  if (Serial.available() > 0) {
    int donneeserie = Serial.read();

    if (donneeserie == 'V') {
      digitalWrite(LedG, HIGH);
      digitalWrite(LedB, LOW);
    }

    if (donneeserie == 'B') {
      digitalWrite(LedB, HIGH);
      digitalWrite(LedG, LOW);
    }
  }
  if (receiver.decode(&results))
  {
    Serial.println(results.value);
    receiver.resume();
  }

}
