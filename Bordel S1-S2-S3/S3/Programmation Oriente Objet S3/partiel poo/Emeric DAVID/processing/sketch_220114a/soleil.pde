class soleil{
  int x, r, v, b; // Position x, Postion Y, et la taille z
  
  
  // Constructeur
  soleil(int x, int r, int v, int b)
  {
    this.x = x;//déclaration des variables
    this.r = r;
    this.v = v;
    this.b = b;
  }

void drawSoleil(){
  circle(x,r,v);
  fill(b);
}


}
