#define   IN1   2
#define   IN2   4
#define   ENB   3
#define   IN3   5
#define   IN4   7
#define   ENA   6





void setup() {
  // put your setup code here, to run once:
pinMode (IN1,OUTPUT);
pinMode (IN2,OUTPUT);
pinMode (ENA,OUTPUT);
pinMode (IN3,OUTPUT);
pinMode (IN4,OUTPUT);
pinMode (ENB,OUTPUT);




}

void loop() {
  // put your main code here, to run repeatedly:
cmd_motor(Left,Forw,85);
cmd_motor(Right,Forw,50);
delay(1000);
cmd_motor(Left,arret,0);
cmd_motor(Right,Forw,80);
delay(1000);
}


void cmd_motor(int motor , int direction, int power )
{
  if(motor==right){
     if (direction==Forw){
         digitalWrite (IN1,HIGH
         digitalWrite (IN2,LOW
         }
         else if (direction ==Backw {
           digitalWrite (IN1,LOW
           digitalWrite (IN2,HIGH
           }
           else { digitalWrite (IN1, HIGH);
                  digitalWrite (IN1, LOW);
                  }
                  analogWrite (ENA, power*2.55);
           j
           
      
         
       
