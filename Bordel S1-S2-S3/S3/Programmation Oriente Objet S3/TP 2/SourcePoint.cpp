#include<iostream>
#include<string>
using namespace std;

#include"Point.h"

int main()
{

	string nomPoint,Reponse;
	float XPoint,YPoint,DeltaX,DeltaY;
	
	cout << "Quel est le nom du point?" << "\n";
	cin >> nomPoint;
	
	cout << "Coordonné X ?" << "\n";
	cin >> XPoint;
	
	cout << "Coordonné Y ?" << "\n";
	cin >> YPoint;
	point PP(nomPoint,XPoint,YPoint);
	
	
	cout << "Quel est le nom du point?" << "\n";
	cin >> nomPoint;
	
	cout << "Coordonné X ?" << "\n";
	cin >> XPoint;
	
	cout << "Coordonné Y ?" << "\n";
	cin >> YPoint;
	point SP(nomPoint,XPoint,YPoint);
	PP.affiche();
	SP.affiche();
	
	cout << "\nDeplacement du premier point\n";
	
	cout << "Coordonné X ?" << "\n";
	cin >> DeltaX;
	
	cout << "Coordonné Y ?" << "\n";
	cin >> DeltaY;
	PP.deplace(DeltaX,DeltaY);
	
	PP.affiche();
	SP.affiche();
}
