#define BP1 4
#define Led1 A3
int etape;
bool etatdlaled=0;
int toto=0;
int n=toto;


void setup() {
  // put your setup code here, to run once:
  pinMode(Led1,OUTPUT);
  pinMode(BP1,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
switch(etape){
  case 0:
  if (digitalRead(BP1)==0)
  {
  etape=1;
  }
  break;


  case 1:
  Serial.println("Nombre de 1 dans toto(="+ String(toto,HEX)+") est : " + n);
  n=n+1;
  etatdlaled=!etatdlaled;
  digitalWrite(Led1,etatdlaled);
  etape=2;
  break;


  case 2:
  if (digitalRead(BP1)==1)
  {
  etape=0;
  }
  break;
}
}
