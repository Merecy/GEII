import processing.serial.*;

soleil Monsoleil;
Serial myPort;
int val;

void setup()
{
  size(200, 200);
  String portName = Serial.list()[0];
  myPort = new Serial(this,"/dev/ttyUSB0", 9600);
  background(255); 
}

void draw()
{
  if ( myPort.available() > 0) {  // If data is available,
    val = myPort.read();// read it and store it in val
  }

  if (val == 0) {  //Si il n'y a aucune valeur sur la serie, le cercle restera noir            
    fill(0,0,0);                   
  } 
  else if (val < 20) {       // En dessous de 20, le cercle sera bleu       
    fill(0,0,255);                  
  } 
  else if (val == 20) {     // a 20, le cercle sera cyan        
    fill(0,255,255);                   
  } 
   else if (val == 21) {    // a 21, le cercle sera orange         
    fill(255,125,0);                  
  } 
  else if (val == 22) {     // a 22, le cercle sera orange fonce        
    fill(255,70,0);                  
  } 
  else if (val > 22) {     // Au dessus de 22, le cercle sera rouge
    fill(255,0,0);                   
  } 
  background(255);        // On fait sa pour avoir un fond toujours blanc
  circle(100,100,100+(val-20)*10); // On fait notre cercle
  
}
