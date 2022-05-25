#define BP1 4
#define BP2 2
#define Led1 A3
int etape, i=0;
bool etatdlaled=0;


void setup() {
  // put your setup code here, to run once:
  pinMode(Led1,OUTPUT);
  pinMode(BP1,INPUT_PULLUP);
  pinMode(BP2,INPUT_PULLUP);
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
  if (digitalRead(BP2)==0)
  {
  etape=3;
  }
  break;


  case 1:
  i=i+1;
  Serial.println(i);
  etape=2;
  break;


  case 2:
  if (digitalRead(BP1)==1)
  {
  etape=0;
  }
  break;


  case 3:
  i=i-1;
  Serial.println(i);
  etape=4;
  break;


  case 4:
  if (digitalRead(BP2)==1)
  {
  etape=0;
  }
  break;
}
}
