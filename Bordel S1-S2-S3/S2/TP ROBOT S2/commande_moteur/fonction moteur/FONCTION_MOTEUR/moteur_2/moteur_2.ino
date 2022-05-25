#define   IN1   2
#define   IN2   4
#define   ENB   6
#define   IN3   7
#define   IN4   5
#define   ENA   3

int i=0;




void setup() {
  // put your setup code here, to run once:
pinMode(ENA , OUTPUT);
pinMode(IN1 , OUTPUT);
pinMode(IN2 , OUTPUT);
pinMode(ENB , OUTPUT);
pinMode(IN3 , OUTPUT);
pinMode(IN4 , OUTPUT);

analogWrite (ENA,127);
analogWrite (ENB,140);
}

void loop() {
for(i;i<4;i++)
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  
  delay(1000);
  
  digitalWrite(IN1,LOW);
  digitalWrite(IN3,LOW);
  
  delay(1000);
  
  digitalWrite(IN2,HIGH);
  digitalWrite(IN4,HIGH);
  
  delay(1000);
  
  digitalWrite(IN2,LOW);
  digitalWrite(IN4,LOW);
  
  delay(1000);
  
}

}
