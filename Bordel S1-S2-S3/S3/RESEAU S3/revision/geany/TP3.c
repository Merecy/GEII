#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (void)
{
		
char data[50];
int socket,check,es,ed,ec;
socket=createSocketTCP();
char IP[] = "192.168.0.25";
int port = 3242;
float dir,speed;

while(1)
{
if (socket==-1)
{
	perror("Erreur critique socket");
	return -1;
}

es=connectServer(socket,IP,port);

if (es==-1)
{
	perror("Erreur critique de connection");
	return -1;
}

ed=receveData(socket,data,50);
if (ed==-1)
{
	perror("Erreur critique de reception");
	return -1;
}

ec=closeSocket(socket);
if (ec==-1)
{
	perror("Erreur critique de fermeture");
	return -1;
}

sscanf(data,"$WIMWV,%f,R,%f,N,A*%d",&dir,&speed,&check);
printf("La direction est %f degre,\nLa vitesse est %f\n\n",dir,speed);

sleep(3);
}
}

