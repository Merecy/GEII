import processing.serial.*;
Serial port;
Cube[] Cubes = new Cube[1]; //Nombre de cube qu'on veut, ici 1
Cible[] Cibles = new Cible[1]; //Nombre de cible qu'on veut

int x0 = 400;
int x1 = 500;
int x2 = 600;
int y0 = 400;
int y1 = 400;
int y2 = 400;
int z0 = 0;
int z1 = 0;
int z2 = 0;
int Long = 50;
int Larg = 50;
int epais = 50;

int randX, randY;


void setup() {
  background(68, 68, 68);
  size(1000, 800, P3D);
  port = new Serial(this, "/dev/ttyUSB0", 9600);
  RandomCible();

  Cubes[0]= new Cube(x0, y0, z0, Long, Larg, epais);
  Cibles[0]= new Cible(randX, randY, z0, Long, Larg, epais);
}

void RandomCible() {
  randX= int(random(0, 1000-2*Larg));
  randY= int(random(0, 800-2*Long));
}

void draw()
{
  fill(0, 255, 0);
  Cubes[0].DrawCube();

  fill(255, 0, 0);
  Cibles[0].DrawCible();
  
  
  if(port.read()=='H'){
   randY=randY+10; 
  }
  
  if(port.read()=='B'){
   randY=randY-10; 
  }
  
  if(port.read()=='D'){
   randX=randX+10; 
  }
  
  if(port.read()=='G'){
   randX=randX-10; 
  }
}
