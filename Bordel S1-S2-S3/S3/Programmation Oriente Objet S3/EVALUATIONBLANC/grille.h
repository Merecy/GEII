#ifndef GRILLE_H
#define GRILLE_H

#include <iostream>
#include <string>

using namespace std;

class grille
{
	
	public:
		//grille(int);
		//~grille();
		void presentation();
		void initialisation(int);
		void questions(int);
		void choix();
		void affiche();
		void finale(int);
		int note;
		int numQ;
		int noteF=0;

	private:
		string nom;
		string prenom;
		string reponse;
		string correction;
		
};
#endif
