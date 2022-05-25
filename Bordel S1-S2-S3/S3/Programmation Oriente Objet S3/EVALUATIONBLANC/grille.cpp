#include <iostream>
#include "grille.h"
#include <fstream>
#include <ctime>

using namespace std;
int note;


ofstream f("POExamen.doc");

void grille::initialisation(int numQuestion)
{
	numQ = numQuestion;
	
	
}

/*grille::~grille()
{
	
}*/

void grille::questions(int)
{
	if (numQ == 1)
	{ 
		cout << "------------------------------------------------------------------- \n";
		cout << "Question "<< numQ<< ": Quelle est la directive permettant d'introduire des instructions situees dans le fichier iostream ?\n";
		cout << "A : inclure \n";
		cout << "B : include \n";
		cout << "C : define \n";
		cout << "--------------------------------------------------------------------- \n";
		correction = 'B';
	}
	
	if (numQ == 2)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Une variable locale c'est :\n";
		cout << "A : une variable declaree hors d'une fonction \n";
		cout << "B : une variable declaree dans une fonction \n";
		cout << "C : une classe \n";
		cout << "-------------------------------------------------\n";
		correction = 'B';
	}
	if (numQ == 3)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Comment declare t on une variable n de type int ? \n";
		cout << "A : int n; \n";
		cout << "B : n int; \n";
		cout << "C : float n; \n";
		cout << "-------------------------------------------------\n";
		correction = 'A';
	}

	if (numQ == 4)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Comment initialise t on explicitement une variable ? \n";
		cout << "A : int n = 10; \n";
		cout << "B : int n (10); \n";
		cout << "C : int n {10}; \n";
		cout << "D : A, B ,C sont correctes \n";
		cout << "-------------------------------------------------\n";
		correction = 'D';
	}
	if (numQ == 5)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Comment s'appelle la declaration d'une fonction ? \n";
		cout << "A : la reference; \n";
		cout << "B : l argument; \n";
		cout << "C : le prototype; \n";
		cout << "-------------------------------------------------\n";
		correction = 'C';
	}

	if (numQ == 6)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Comment transmet on par argument une valeur a l'aide d'une fonction ? \n";
		cout << "A : fonction(valeur); \n";
		cout << "B : valeur(fonction); \n";
		cout << "C : fonction(reference); \n";
		cout << "-------------------------------------------------\n";
		correction = 'A';
	}
	if (numQ == 7)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Quelle expression a la bonne synthaxe pour fonctionner sans erreur ? \n";
		cout << "A : for( i++; i<= nbrMax; int i = 0 ); \n";
		cout << "B : for(switch i; i++, case i); \n";
		cout << "C : for( int i = 0; i<= nbrMax; i++ ); \n";
		cout << "-------------------------------------------------\n";
		correction = 'C';
	}

	if (numQ == 8)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Que signifie cet operateur:  <= ? \n";
		cout << "A : egale a \n";
		cout << "B : inferieur ou egale a \n";
		cout << "C : different de \n";
		cout << "-------------------------------------------------\n";
		correction = 'B';
	}
	if (numQ == 9)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Une variable globale est :  \n";
		cout << "A : declaree dans une fonction \n";
		cout << "B : connue de toutes les fonctions \n";
		cout << "C : toujours de type int \n";
		cout << "-------------------------------------------------\n";
		correction = 'B';
	}

	if (numQ == 10)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Comment se nomme l'espace de nom dit standard ? \n";
		cout << "A : iostream \n";
		cout << "B : int \n";
		cout << "C : std \n";
		cout << "-------------------------------------------------\n";
		correction = 'C';
	}
	if (numQ == 11)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Quelle est l'utilitee de declarer des membres de maniere public ? \n";
		cout << "A : les membres sont accessibles depuis l'exterieur de la classe\n";
		cout << "B : les membres sont accessibles uniquement aux fonctions membres de la classe\n";
		cout << "C : les membres sont initialises a 0  \n";
		cout << "-------------------------------------------------\n";
		correction = 'A';
	}

	if (numQ == 12)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Comment creer un objet monPoint de la classe point ?  \n";
		cout << "A : point monPoint\n";
		cout << "B : monPoint point \n";
		cout << "C : point.monPoint \n";
		cout << "-------------------------------------------------\n";
		correction = 'A';
	}
	if (numQ == 13)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Comment s'appelle l'instruction permettant d'attribuer des valeurs aux donnees d'un objet ?  \n";
		cout << "A : le prototype\n";
		cout << "B : le destructeur \n";
		cout << "C : le constructeur \n";
		cout << "-------------------------------------------------\n";
		correction = 'C';
	}

	if (numQ == 14)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Comment s'appelle l'instruction permettant de detruire un objet ?  \n";
		cout << "A : le prototype\n";
		cout << "B : le destructeur \n";
		cout << "C : le constructeur \n";
		cout << "-------------------------------------------------\n";
		correction = 'B';
	}
	if (numQ == 15)
	{
		
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Le constructeur du prototype de la classe fregate est defini de cette maniere : fregate(string). Comment creer un objet FREMM a cette classe ? \n";
		cout << "A : fregate FREMM (nomFregate)\n";
		cout << "B : fregate FREMM() \n";
		cout << "C : FREMM fregate() \n";
		cout << "-------------------------------------------------\n";
		correction = 'A';
	}

	if (numQ == 16)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Le constructeur de la classe fregate est defini de cette maniere : fregate(string). Comment est defini le destructueur \n";
		cout << "A : destruct(fregate)\n";
		cout << "B : ~fregate() \n";
		cout << "C : ~fregate(string) \n";
		cout << "-------------------------------------------------\n";
		correction = 'B';
	}
	if (numQ == 17)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Une fonction affiche() est une fonction membre de la classe fregate. Un objet FTI a ete cree. Comment appeler la fonction affiche ? \n";
		cout << "A : fregate.affiche()\n";
		cout << "B : FTI.affiche() \n";
		cout << "C : FREMM.affiche() \n";
		cout << "-------------------------------------------------\n";
		correction = 'B';
	}

	if (numQ == 18)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Une fonction affiche() est une fonction membre de la classe fregate. Un objet FREMM a ete cree. Comment appeler la fonction affiche ? \n";
		cout << "A : fregate.affiche()\n";
		cout << "B : FTI.affiche() \n";
		cout << "C : FREMM.affiche() \n";
		cout << "-------------------------------------------------\n";
		correction = 'C';
	}
	if (numQ == 19)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Quels sont les fichiers necessitant une compilation ? \n";
		cout << "A : les fichiers .h\n";
		cout << "B : les fichiers .cpp \n";
		cout << "C : les fichiers .h et .cpp \n";
		cout << "-------------------------------------------------\n";
		correction = 'B';
	}

	if (numQ == 20)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": En compilation separee, dans quel fichier se trouve la declaration de la classe point ? \n";
		cout << "A : point.h\n";
		cout << "B : point.cpp\n";
		cout << "C : source.cpp \n";
		cout << "-------------------------------------------------\n";
		correction = 'A';
	}
	if (numQ == 21)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ":  Quelles sont les deux fonctions essentielles sous l'IDE ARDUINO ? \n";
		cout << "A : SETUP et LOOP\n";
		cout << "B : DRAW et LOOP\n";
		cout << "C : AFFICHE et INITIALISATION\n";
		cout << "-------------------------------------------------\n";
		correction = 'A';
	}
	if (numQ == 22)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ":  Le constructeur de la classe LiquidCrystal_I2C est defini de cette maniere : LiquidCrystal_I2C(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows) Comment creer un objet se nommant LCD de cette classe ? \n";
		cout << "A : LiquidCrystal_I2C (LCD); \n";
		cout << "B : LiquidCrystal_I2C LCD(0XF,12,6);\n";
		cout << "C : LiquidCrystal_I2C MonLCD(0XF,12,6);\n";
		cout << "-------------------------------------------------\n";
		correction = 'B';
	}
	if (numQ == 23)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ":  Un objet LCD est cree de la classe LiquidCrystal_I2C. Comment utiliser la fonction membre  clear() ? \n";
		cout << "A : LCD.clear(); \n";
		cout << "B : clear();\n";
		cout << "C : LiquidCrystal_I2C LCD clear();\n";
		cout << "-------------------------------------------------\n";
		correction = 'A';
	}
	if (numQ == 24)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ":  Deux Arduino sont connectes en I2C. Le fonction permettant de choisir l'esclave  et demarrer une transmission est ? \n";
		cout << "A : wire.beginTransmission(adressedelesclave); \n";
		cout << "B : wire.requestFrom(adressedelesclave,1);\n";
		cout << "C : wire.endTransmission();\n";
		cout << "-------------------------------------------------\n";
		correction = 'A';
	}
	if (numQ == 25)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ":  Quel est le nom de la bibliothèque Arduino permettant de faire communiquer des appareils en I2C ? \n";
		cout << "A : Serial; \n";
		cout << "B : IRremote;\n";
		cout << "C : Wire;\n";
		cout << "-------------------------------------------------\n";
		correction = 'C';
	}
	if (numQ == 26)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ":  Comment se nomme la condition permettant de debuter une liaison via bus I2C? \n";
		cout << "A : begin; \n";
		cout << "B : Start;\n";
		cout << "C : Pause;\n";
		cout << "-------------------------------------------------\n";
		correction = 'B';
	}
	if (numQ == 27)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Sans prendre en compte le bit R/W, le protocole du bus I2C defini l'adresse de l'eclave sous combien de bits ? \n";
		cout << "A : 1 octet ; \n";
		cout << "B : 8 bits;\n";
		cout << "C : 7 bits;\n";
		cout << "-------------------------------------------------\n";
		correction = 'C';
	}
	if (numQ == 28)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ":  Dans le protocole du bus I2C, comment se nomme le bit d'acquittement  ? \n";
		cout << "A : ACK ; \n";
		cout << "B : NACK;\n";
		cout << "C : SLAVE;\n";
		cout << "-------------------------------------------------\n";
		correction = 'A';
	}
	if (numQ == 29)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Comment se nomme les deux signaux essentiels d'une communication via bus I2C  ? \n";
		cout << "A : ACK et NACK ; \n";
		cout << "B : SDA et SCL;\n";
		cout << "C : Strat et pause;\n";
		cout << "-------------------------------------------------\n";
		correction = 'B';
	}
	if (numQ == 30)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Dans le protocole du bus I2C, lors de l'emission par le maitre de l'octet de donnees, que doit repondre l'esclave pour confirmer la bonne reception ? \n";
		cout << "A : ACK  ; \n";
		cout << "B : NACK;\n";
		cout << "C : Strat;\n";
		cout << "-------------------------------------------------\n";
		correction = 'A';
	}
	if (numQ == 31)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Comment initialiser une liaison serie ?\n";
		cout << "A : Serial.start(9600);  \n";
		cout << "B : Serial.begin(9600);\n";
		cout << "C : Serial.ack(9600);\n";
		cout << "-------------------------------------------------\n";
		correction = 'B';
	}
	if (numQ == 32)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Comment s'appelle le logiciel utilise en cours pour faire de l'intrefacage graphique ?\n";
		cout << "A : Arduino;  \n";
		cout << "B : Geni;\n";
		cout << "C : Processing;\n";
		cout << "-------------------------------------------------\n";
		correction = 'C';
	}
	if (numQ == 33)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Quelles sont les deux fonctions de bases de Processing ?\n";
		cout << "A : SETUP et LOOP;  \n";
		cout << "B : SETUP et DRAW;\n";
		cout << "C : LOOP et DRAW;\n";
		cout << "-------------------------------------------------\n";
		correction = 'B';
	}
	if (numQ == 34)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Sous Processing, quelle est la fonction permettant d'ajuster la taille d'une fenetre ?\n";
		cout << "A : size();  \n";
		cout << "B : fill();\n";
		cout << "C : bakground();\n";
		cout << "-------------------------------------------------\n";
		correction = 'A';
	}
	if (numQ == 35)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Sous Processing une classe Cube et un objet moncube ont ete crees. Comment initialiser un nouvel objet ?\n";
		cout << "A : moncube = new Cube() ;  \n";
		cout << "B : moncube =  Cube();\n";
		cout << "C : Cube = new moncube();\n";
		cout << "-------------------------------------------------\n";
		correction = 'A';
	}
	if (numQ == 36)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Sous Processing,comment generer un entier aleatoire i compris entre 1 et 10  ?\n";
		cout << "A : i = (1 + random(10)) ;  \n";
		cout << "B : i =  int (1 + random(10));\n";
		cout << "C : i =   1 + random(10);\n";
		cout << "-------------------------------------------------\n";
		correction = 'B';
	}
	if (numQ == 37)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Sous Processing,un objet monport de la classe Serial a ete cree. Comment ecrire 'R' sur le port serie   ?\n";
		cout << "A : monPort = write('R') ;  \n";
		cout << "B : monport.write('R');\n";
		cout << "C : 'R' = monport;\n";
		cout << "-------------------------------------------------\n";
		correction = 'B';
	}
	if (numQ == 38)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Sous Processing,comment rendre le fond de la fenetre jaune   ?\n";
		cout << "A : backgroud('jaune') ;  \n";
		cout << "B : background(255,0,0);\n";
		cout << "C : background(255,255,0);\n";
		cout << "-------------------------------------------------\n";
		correction = 'C';
	}
	if (numQ == 39)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Sous Processing,la creation d'une classe se fait :   ?\n";
		cout << "A : avec un fichier .h ;  \n";
		cout << "B : avec un fichier .cpp;\n";
		cout << "C : avec un nouvel onglet;\n";
		cout << "-------------------------------------------------\n";
		correction = 'C';
	}
	if (numQ == 40)
	{
		cout << "-------------------------------------------------\n";
		cout << "Question " << numQ << ": Sous Processing,une fonction membre draw() a ete cree dans la classe CUBE. Un objet monCube a ete cree. Comment appeler la fonction   ?\n";
		cout << "A : monCube.draw() ;  \n";
		cout << "B : draw();\n";
		cout << "C : CUBE.draw();\n";
		cout << "-------------------------------------------------\n";
		correction = 'A';
	}
}
void grille::choix()
{
	cout << "Votre choix :";
	cin >> reponse;
}
	
	
void grille::affiche()
{
	cout << "\n------------------------|| "<<"SOLUTION "<<numQ<<" ||-----------------------\n";
	
	cout << " Votre choix a la question numero " << numQ << " est: " << reponse<< "\n";
	cout << " La reponse est  " << correction << "\n";
	if (reponse == correction)
	{
		cout << " BRAVO \n";
	    note= note+1;
	}
	else
	{
		cout << "FAUX \n";
	}
	cout << "----------------------------------------------------------------\n";

	f << "\n------------------------|| " << "SOLUTION " << numQ << " ||-----------------------\n";

	f << " Votre choix a la question numero " << numQ << " est: " << reponse << "\n";
	f << " La reponse est:  " << correction << "\n";
	if (reponse == correction)
	{
		f << " BRAVO \n";
		
	}
	else
	{
		f << "FAUX \n";
	}
	f << "----------------------------------------------------------------\n";
	
	
}
void grille::presentation()
{
	time_t now = time(NULL);
	char str[26];
	//ctime_s(str,sizeof str,&now);

	cout << "Nom : ";
	cin >> nom;
	f << "Nom : " << nom << "\n";

	cout << "Prenom : ";
	cin >> prenom;
	f << "Prenom : " << prenom;
	f << "                            " << str;
	f << "________________________________________________________________ \n";
	f <<"                        POO GEII DUT2          " <<"\n";

	f << "________________________________________________________________ \n";

	
}

void grille::finale(int nombre)
{
	time_t now = time(NULL);
	char str1[26];
	//ctime_s(str1, sizeof str1, &now);
	f << "________________________________________________________________ \n";
	cout << "Votre note : " << noteF << "/" << nombre;
	f << "Votre note : " << noteF << "/" << nombre<<"\n";
	f << "________________________________________________________________ \n";
	f << "                            " << str1;

	
}
