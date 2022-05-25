import processing.serial.*;
Serial port;
Cube MesCubes ;
Cible[] MesCibles = new Cible[2];

int x0 = 125;
int y0 = 75;

int L = 50;
int l = 50;
int e = 50;

int xc0;
int yc0;
int xc1;
int yc1;

int compteur= 0;
int couleur;
int value;


void setup()
{
  size(300, 200, P3D); //3d
  port = new Serial(this, "/dev/ttyUSB0", 9600);
  //debut();
  initialisationcible();
}

void initialisationcible()
{

  xc0 = int(random(0, 300-l));
  yc0 = int(random(0, 200-L));
  xc1 = int(random(0, 300-l));
  yc1 = int(random(0, 200-L));
  couleur= int(random(1, 3));
}

void debut()
{
  while (value==0) {
    PFont  monfond;
    background (0, 0, 0);
    fill(255, 255, 255);
    monfond  = createFont("Georgia", 32);
    textFont(monfond);
    text("Commencer ?", 20, 20);
  }
}

void mouseClicked() {
  if (value == 0) {
    value = 255;
  } else {
    value = 0;
  }
}

void reception()
{
  int pas = 1;
  while (port.available() > 0) {
    String inByte = port.readString();
    String[] verificationD = match(inByte, "16742535");
    String[] verificationG = match(inByte, "16732335");
    String[] verificationH = match(inByte, "16752735");
    String[] verificationB = match(inByte, "16728255");

    println(x0, y0);

    //Droite
    if (verificationD != null)
    {
      x0 = x0+pas;
    }
    //gauche
    if (verificationG != null  )
    {
      x0 = x0-pas;
    }
    //Haut
    if (verificationH != null )
    {
      y0 = y0-pas;
    }
    if (verificationB != null )
    {
      y0 = y0+pas;
    }
  }
}
void verification()
{
  int gain = 0;
  int s =0;


  text("temps", 10, 10);

  s = millis()/1000 - gain;
  text(s, 50, 10);

  if (x0 == xc0 && y0 == yc0 && couleur==1)
  {
    background (0, 255, 0);
    compteur++;
    gain =  gain + 10;
    initialisationcible();
  }

  if (x0 == xc1 && y0 == yc1 && couleur==2)
  {
    background (0, 255, 0);
    compteur++;
    gain =  gain + 10;
    initialisationcible();
  }

  if (s == 120)
  {
    fin ();
  }
}
void fin()
{
  PFont  monfond;
  background (0, 0, 255);
  fill(255, 0, 0);
  monfond  = createFont("Georgia", 32);
  textFont(monfond);
  text("FIN", 120, 90);
  text("RESULTAT : ", 100, 120);
  text(compteur, 150, 140);

  stop();
}




void draw()
{
  background (255, 255, 255);

  MesCibles[0] = new Cible(xc0, yc0, 0, 0, 255, 0);
  MesCibles[1] = new Cible(xc1, yc1, 0, 0, 0, 255);
  MesCubes =  new Cube(x0, y0, 0);

  verification();
  MesCubes.drawCube();

  MesCibles[0].drawCible();
  MesCibles[1].drawCible();

  reception();

  if (couleur==1) {
    port.write('V');
  }

  if (couleur==2) {
    port.write('B');
  }
}
