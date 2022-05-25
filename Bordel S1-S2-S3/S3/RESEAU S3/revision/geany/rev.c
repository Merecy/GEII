#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *serverAddress ="192.168.0.27";
int port=5246;
char data[50];

int main (void){
	int socket = createSocketTCP();
	if (socket==-1){
		perror("Erreur critique socket");
	    return -1;
	}
	
	int error = connectServer(socket,serverAddress,port);
	if (error == -1){
		perror("Erreur critique socket");
	    return -1;
	}
	
	error=receveData(socket,data,50);
	if (error == -1){
		perror("Erreur critique socket");
	    return -1;
	}
	
	error=closeSocket(socket);
	if (error == -1){
		perror("Erreur critique socket");
	    return -1;
	}
	
	sscanf(data,"$WIMWV,%s,R,%s,N,A*%s\r\n",&dir, &speed,
	
	
	
}
