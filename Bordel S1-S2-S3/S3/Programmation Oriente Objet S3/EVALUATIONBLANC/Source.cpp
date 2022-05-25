#include <iostream>
#include "grille.h"
#include <string>
#include <vector>
#include <stdlib.h>
#include <random>
#include <algorithm>
#include <iterator>





using namespace std;
const int nbrMax = 40;

int compteur= 0;

int main()
{
	int numQ;
	
	int nbr = 0;
	grille eleve;
	eleve.presentation();
	cout << "Evaluation POO DUT 2" << "\n";
	cout << "Combien de question voulez vous ? : " << "\n";
	cin >> nbr;

	

	vector <grille> question(nbr+1);
	
	vector <int> v(nbrMax+1);

	for (int i = 1; i < nbrMax+1; i++)
	{
		v[i] = i;
	}
	random_device rd;
	mt19937 g(rd());
	shuffle(v.begin()+1, v.end(), g);

	for (int j = 1; j < nbr + 1; j++)
	{
		question[j].initialisation(v[j]);
		question[j].questions(v[j]);
		question[j].choix();
	}
	
	
	for (int i = 1; i < nbr+1; i++)
	{
		question[i].affiche();
		if (question[i].note == 1)
		compteur++;
	}

	eleve.noteF = compteur;
	eleve.finale(nbr);
	
	
}
