unsigned int B = -10, n=0;


void setup() {
  Serial.begin(9600);
  Serial.println(B,BIN);
  for (int i = 0; i < 8; i++) {
    
    if ((B & 1) == 1)
    {
      n++;
      Serial.println(B,BIN);
    }
    
    B = B >> 1;
  }
  Serial.print("Nombre de bit 1 : ");
  Serial.println(n);

}

void loop() {

}
