#define temp A0
#define npot A1
#define ventilateur 4
#define halogene 3


//#define temps


unsigned long previousMillis = 0;
const long interval = 1000;
unsigned long previousMillis2 = 0;
const long interval2 = 10000;
float vref = 4.6;
bool cmd = 0;
int i = 0, consigne;

void setup() {
  // put your setup code here, to run once:
  pinMode(temp, INPUT);
  pinMode(npot, INPUT);
  pinMode(ventilateur, OUTPUT);
  pinMode(halogene, OUTPUT);
  Serial.begin(57600);
  
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    int valeur = analogRead(temp);
    float valeurc = (valeur * vref) / 1023;
    float tempc = valeurc * 100;
    //Serial.print("temperature :");
    //Serial.print(temp);
    //Serial.print(" / ");
    //Serial.print(valeurc);
    //Serial.print(" V");
    //Serial.print(" / ");
    Serial.print(tempc);
    //Serial.println(" degre");

    consigne = map(analogRead(npot),0,1023,20,120);
    Serial.print(",");
    Serial.println(consigne);
    
    float delta = consigne - tempc;
    int commande = delta *100;
    commande= constrain(commande,0,100);

    analogWrite(halogene,commande);
    digitalWrite(ventilateur, LOW);
    
    if (delta <= -5)
    {
      digitalWrite(ventilateur,HIGH);
    }

    


  }

#ifdef temps
  if (currentMillis - previousMillis2 >= interval2) {
    previousMillis2 = currentMillis;
    {
      cmd = !cmd;
      if (cmd == 0)
      {
        analogWrite(halogene, 0);
        digitalWrite(ventilateur, HIGH);
      }
      else
      {
        analogWrite(halogene, 50);
        digitalWrite(ventilateur, LOW);
      }
    }
  }
#endif
}
