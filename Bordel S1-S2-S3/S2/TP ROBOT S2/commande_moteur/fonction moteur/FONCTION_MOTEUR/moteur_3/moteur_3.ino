#define IN1 4
#define IN2 2
#define ENA 3
#define IN3 5
#define IN4 7
#define ENB 6
#define Left 0
#define Right 1
#define Forw 1
#define Backw -1
#define Stop 0


int i=0;
void cmd_motor(int,int,int);


void setup() {
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
}

void loop(){
for(i;i<1;i++)
  {
  //cmd_motor(Right,Forw,127);
  //cmd_motor(Left,Forw,140);
  //delay(2000);
  //cmd_motor(Right,Forw,77);
  //cmd_motor(Left,Forw,140); 
  //delay(600);
  //cmd_motor(Right,Backw,127);
  //cmd_motor(Left,Backw,140);
  //delay(1000);
  //cmd_motor(Right,Backw,127);
  //cmd_motor(Left,Backw,90);
  //delay(700);
  //cmd_motor(Right,Backw,127);
  //cmd_motor(Left,Backw,140);
  //delay(1000);
  //cmd_motor(Left,Stop,0);
  //cmd_motor(Right,Stop,0);
  cmd_motor(Right,Forw,127);
  cmd_motor(Left,Forw,140 );
  delay(1000);
  }
}

void cmd_motor(int motor, int direct, int power){
 power=power;
    
    if(motor==Right)
      {
       if(direct==Forw)
       {
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
       }
       if(direct==Backw)
      {
       digitalWrite(IN1,LOW);
       digitalWrite(IN2,HIGH);
      }
      if(direct==Stop)
      { 
       digitalWrite(IN1, LOW);
       digitalWrite(IN2, LOW);       
      }
      analogWrite(ENA,power);
      }
    if(motor==Left)
      {
       if(direct==Forw)
       {
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW); 
       }
       if(direct==Backw)
      {
       digitalWrite(IN3, LOW);
       digitalWrite(IN4,HIGH); 
      }
      if(direct==Stop)
      {  
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,LOW); 
      }
      analogWrite(ENB,power);
      }
}
