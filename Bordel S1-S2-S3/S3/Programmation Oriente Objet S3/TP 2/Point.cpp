#include<iostream>
#include<string>
using namespace std;

#include"Point.h"

// Definition des fonctions membres de la classe point
point::point(string nomPoint, float XPoint, float YPoint)// :: Operateur "resolution de portée"
{
	nom = nomPoint;
	X = XPoint;
	Y = YPoint;	
}

point::~point()
{
}

void point::affiche()
{
	cout << "Je suis " << nom << " et je suis au coordonné(" << X << ";" << Y << ")\n";
}

void point::deplace(float DeltaX,float DeltaY)
{
	X = X + DeltaX;
	Y = Y + DeltaY;
}
