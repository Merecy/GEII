class Cible {

  // Proprietes
  int x, y, z, r, g, b; // coordonnées du point "haut/gauche"


  // Constructeur
  Cible(int x, int y, int z, int r, int g, int b)
  {
    this.x = x;//déclaration
    this.y = y;
    this.z = z;
    this.r = r;
    this.g = g;
    this.b = b;
  }

  void drawCible()
  {
    beginShape(QUADS);
    fill(r, g, b);
    // Face 1
    vertex(x, y, z);
    vertex(x + L, y, z );
    vertex(x + L, y + l, z);
    vertex(x, y + l, z);

    // Face 2
    vertex(x, y, z);
    vertex(x + L, y, z);
    vertex(x + L, y, z +e);
    vertex(x, y, z +e);

    // Face 3
    vertex(x, y, z +e);
    vertex(x + L, y, z + e);
    vertex(x + L, y + l, z + e);
    vertex(x, y + l, z + e);

    // Face 4
    vertex(x + L, y, z);
    vertex(x + L, y + l, z);
    vertex(x + L, y + l, z + e);
    vertex(x + L, y, z + e);

    // Face 5
    vertex(x, y, z);
    vertex(x, y + l, z);
    vertex(x, y + l, z + e);
    vertex(x, y, z + e);

    // Face 6
    vertex(x, y + l, z);
    vertex(x + L, y + l, z);
    vertex(x + L, y + l, z + e);
    vertex(x, y + l, z + e);

    endShape();
  }
}
