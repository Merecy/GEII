#ifndef TP_RESEAU_H
#define TP_RESEAU_H

/***********************************************************************
 Rôle: Crée un socket pour le protocole TCP 
Valeur retournée: -1 si erreur, le numéro du socket sinon
***********************************************************************/
int createSocketTCP(void);

/***********************************************************************
Rôle:Connecte un client (machine sur laquelle tourne le programme) avec  
un serveur repéré par son adresse et son numéro de port. 
Arguments:       
	-sock: descripteur de la socket créée (valeur retournée par la 
			fonction createSocket)
	-serverAddress: adresse du serveur en notation décimale pointée
	-port: port destinataire                          
Valeur retournée: -1 si erreur, 0 sinon
***********************************************************************/
int connectServer(int socket, char *serverAddress, int port);

/***********************************************************************
Rôle:Envoie les données passées en argument au serveur avec qui l'on est
connecté
Arguments: 
	-socket: descripteur de la socket 
	-data : Tableau qui contient la chaîne de caractères à envoyer.
Valeur retournée: -1 si erreur, le nombre de caractères envoyés sinon
***********************************************************************/	   
int sendData(int socket, char *data);

/***********************************************************************
Rôle:Reçoit des données du serveur avec qui l'on est connecté
Arguments: 
-	socket: descripteur de la socket 
-	data : Tableau qui contient la chaîne de caractère des données reçues.
-   Size: Taille du tableau Donnees
Valeur retournée: -1 si erreur, le nombre de caractères reçus sinon.
***********************************************************************/
int receveData(int socket, char *data, int size);

/***********************************************************************
Rôle:Crée un serveur sur cette machine 
Arguments: 
	-socket: descripteur de la socket créée (valeur retournée par la
			fonction createSocket)
	-port : Numéro de port du service créé.
Valeur retournée: -1 si erreur, 0 sinon.
***********************************************************************/   
int createServer(int socket, int port);

/***********************************************************************
Rôle:Une fois créé, met le serveur en écoute (attente d'une connexion
     client) cette fonction est bloquante.
Arguments: 
	-socket: descripteur de la socket créée (valeur retournée par la 
			fonction createSocket)
Valeur retournée: -1 si erreur, le numéro de la socket sur laquelle il 
                  faut communiquer sinon.
***********************************************************************/
int waitConnexionClient(int socket);

/***********************************************************************
Rôle: Ferme la connexion
Arguments: 
-	socket: descripteur de la socket 
 Valeur retournée: -1 si erreur, 0 sinon 
***********************************************************************/
int closeSocket(int socket);

#endif
