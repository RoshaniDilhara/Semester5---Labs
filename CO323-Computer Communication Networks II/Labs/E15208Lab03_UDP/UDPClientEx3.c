#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc,char** argv){

	int sockfd,n;
	struct sockaddr_in serverAddress;
	char* sendLine="Hello UDP Server! This is a client";
	char recveline[1000];
	if(argc!=3){
		//take number of sentences it is going to send as input
		printf("usage: %s <IP address> <NoOfSentences>\n",argv[0] );
		return -1;
	}

	sockfd=socket(AF_INET,SOCK_DGRAM,0);

	bzero(&serverAddress,sizeof(serverAddress));

	serverAddress.sin_family=AF_INET;
	serverAddress.sin_addr.s_addr=inet_addr(argv[1]);
	serverAddress.sin_port=htons(32000);

	sendto(sockfd,argv[2],strlen(sendLine),0,(struct sockaddr*)&serverAddress,sizeof(serverAddress));
	n=recvfrom(sockfd,recveline,1000,0,NULL,NULL);
	recveline[n]=0;
	printf("Received: %s\n", recveline);

	int j;

	char* inputLine;size_t len = 0;

	j=0;
	while(j<atoi(argv[2])){

		getline(&inputLine, &len, stdin);
		
		sendto(sockfd,inputLine,strlen(sendLine),0,(struct sockaddr*)&serverAddress,sizeof(serverAddress));
		n=recvfrom(sockfd,recveline,1000,0,NULL,NULL);
		recveline[n]=0;
		printf("Received: %s", recveline);
	j++;
	}
	return 0;
}
