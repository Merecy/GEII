class Cube {

  //Proprietes
  int x; //Coordonné x du cube
  int y; //Coordonné y du cube
  int z; //Coordonné z du cube
  int L; //Longueur du cube
  int l; //Largeur du cube
  int e; //Epaisseur du cube

  //Constructeur
  Cube(int x, int y, int z, int L, int l, int e)
  {
    this.x = x;
    this.y = y;
    this.z = z;
    this.L = L;
    this.l = l;
    this.e = e;
  }

  void DrawCube()
  {
    beginShape(QUADS);
    //Face 1 (devant)
    vertex(x, y, z);
    vertex(x + L, y, z);
    vertex(x + L, y+l, z);
    vertex(x, y+l, z);

    //Face 2 (Dessous)
    vertex(x, y, z);
    vertex(x +L, y, z);
    vertex(x+L, y, z+e);
    vertex(x, y, z+e);

    //Face 3 (Derriere)
    vertex(x, y, z+e);
    vertex(x+L, y, z+e);
    vertex(x+L, y+l, z+e);
    vertex(x, y+l, z+e);

    //Face 4 (Droite)
    vertex(x+L, y, z);
    vertex(x+L, y+l, z);
    vertex(x+L, y+l, z+e);
    vertex(x+L, y, z+e);

    //Face 5 (Gauche)
    vertex(x, y, z);
    vertex(x, y+l, z);
    vertex(x, y+l, z+e);
    vertex(x, y, z+e);

    //Face 6 (Dessus)
    vertex(x, y+l, z);
    vertex(x+L, y+l, z);
    vertex(x+L, y+l, z+e);
    vertex(x, y+l, z+e);

    endShape();
  }
}
