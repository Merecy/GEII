#include<iostream>
#include<string>
using namespace std;

#include"Fregate.h"

int main()
{

	string nomFregate;
	cout << "Quel est le nom de la fregate ?" << "\n";
	cin >> nomFregate;
	fregate FREMM(nomFregate);
	FREMM.affiche();
	
}
