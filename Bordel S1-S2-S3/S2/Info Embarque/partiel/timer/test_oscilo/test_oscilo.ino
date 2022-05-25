#define Dout 7
#define Led2 A2 
#define BP2 2


void setup() {
pinMode(Led2,OUTPUT);
  
pinMode(Dout,OUTPUT);
digitalWrite(Dout,0);
TCCR1A=0; //Timer en mode normal(sa bouge pas)
TCCR1B=3; //fosc divise par 1024 
TIMSK1=1;  // Its a chaque debordement
TCNT1=34286;  //1ere valeur du cycle
sei();

attachInterrupt(digitalPinToInterrupt(BP2), chang, RISING);
pinMode(BP2, INPUT_PULLUP);
}
 

void loop() {

}

void chang()
{
  static bool dive;
  dive=!dive;
  if (dive) TCCR1B=4;
  else TCCR1B=3;
}


ISR(TIMER1_OVF_vect)
{
  static bool etatDout;
  TCNT1=34286;
  etatDout=!etatDout;
  digitalWrite(Dout,etatDout);
  digitalWrite(Led2,etatDout);
}
