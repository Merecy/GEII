class Cube {

  // Proprietes
  int x, y, z; // corrdonnées du point "haut/gauche"
  
  
  // Constructeur
  Cube(int x, int y, int z)
  {
    this.x = x;//déclaration
    this.y = y;
    this.z = z;
   
  }

  void drawCube()
  {
    beginShape(QUADS);
    // Face 1 
    fill(255,0,255);
    vertex(x,y,z); 
    vertex(x + L,y,z ); 
    vertex(x + L ,y + l,z); 
    vertex(x,y + l,z); 
   
    // Face 2
    vertex(x,y,z); 
    vertex(x + L,y,z); 
    vertex(x + L,y,z +e);
    vertex(x,y,z +e); 
   
    // Face 3
    vertex(x , y, z +e);
    vertex(x + L , y, z + e);
    vertex(x + L, y + l, z + e);  
    vertex(x,y + l ,z + e); 
    
    // Face 4
    vertex(x + L, y , z);
    vertex(x + L  , y + l, z); 
    vertex(x + L, y + l, z + e);
    vertex(x + L, y , z + e); 
     
    // Face 5
    vertex(x, y, z); 
    vertex(x , y + l, z);
    vertex(x, y + l, z + e);
    vertex(x , y, z + e); 
     
    // Face 6
    vertex(x, y + l, z); 
    vertex(x + L , y + l, z);
    vertex(x + L , y + l, z + e);
    vertex(x , y + l, z + e); 
    
    endShape(); 

  }
  
 
}
