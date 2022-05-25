int Litre=0, Litrea=0;
float debit=0.0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
for(int i=0;i<20;i++){
  Litre=i+Litrea;
  delay(1000);
}
debit=(float)(Litre-Litrea)/20;
Serial.print(Litre);
Serial.print(" ; ");
Serial.print(Litrea);
Serial.print(" ; ");
Serial.println(debit);
Litrea=Litre;
}
