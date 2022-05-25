#include<iostream>
#include<string>
using namespace std;

#include"Fregate.h"

// Definition des fonctions membres de la classe fregate
fregate::fregate(string nomFregate)// :: Operateur "resolution de portée"
{
	nom = nomFregate;
}

fregate::~fregate()
{
}

void fregate::affiche()
{
	cout << "Mon nom est " << nom << "\n";
}
