#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (void)
{
int socket;
socket=createSocketTCP();
int port = 3242;
char data[50]="\n\n\n      Ma bite et mon couteau \n\n\n\n";

while(1){
	
if (socket==-1)
{
	perror("Erreur critique socket");
	return -1;
}

int error =createServer(socket, port);

if (error==-1)
{
	perror("Erreur critique socket");
	return -1;
}

int truc = waitConnexionClient(socket);

int test = sendData(truc,data);

test = closeSocket(socket);

if (test==-1)
{
	perror("Erreur critique socket");
	return -1;
}
}
}
