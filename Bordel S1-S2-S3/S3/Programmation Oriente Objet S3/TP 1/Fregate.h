#ifndef FREGATE_H
#define FREGATE_H

#include<iostream>
#include<string>
using namespace std;

// Declaration de la classe fregate
class fregate
{
// Declaration des membres publics
public:
	fregate(string);
	~fregate();
	void affiche();
	
// Declaration des membres privés	
private:
	string nom;
	
};
#endif
