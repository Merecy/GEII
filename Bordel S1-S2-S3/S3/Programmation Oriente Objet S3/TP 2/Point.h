#ifndef POINT_H
#define POINT_H

#include<iostream>
#include<string>
using namespace std;

// Declaration de la classe point
class point
{
// Declaration des membres publics
public:
	point(string,float,float);
	~point();
	void affiche();
	void deplace(float,float);
	
// Declaration des membres privés	
private:
	string nom;
	float X;
	float Y;
	
};
#endif
