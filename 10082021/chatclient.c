#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define MAXLINE 1024
#define CL_PORT 8080
#define SERV_PORT 9090

int main(int argc, char **argv) {
    int client_number;
    client_number = (*argv[1]) - 48;

int sockfd;
//char buffer[MAXLINE];

struct sockaddr_in servaddr, cliaddr;
if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
}
memset(&servaddr, 0, sizeof(servaddr));
memset(&cliaddr, 0, sizeof(cliaddr));

// Filling own information
cliaddr.sin_family = AF_INET; // IPv4
cliaddr.sin_addr.s_addr = INADDR_ANY;
cliaddr.sin_port = htons(CL_PORT + client_number);

// Bind the socket with the server address
if ( bind(sockfd, (const struct sockaddr *)&cliaddr,
			sizeof(cliaddr)) < 0 )
{
    perror("bind failed");
	exit(EXIT_FAILURE);
}

// Filling own information
servaddr.sin_family = AF_INET; // IPv4
servaddr.sin_addr.s_addr = INADDR_ANY;
servaddr.sin_port = htons(SERV_PORT);


int len, n, from, to, from_message;


while(1) {
	
	printf("Enter r for recieve and s for send mode");
	char c;
	scanf(" %c",&c);
	//scanf whether you want to be in send mode or recv mode?

	if (c=='s') 
	{
		char buffer[1024];
		printf("Enter message");
		
		scanf("%s",buffer);
    	len = sizeof(servaddr);
    	sendto(sockfd, (const char *)buffer, strlen(buffer),0, (const struct sockaddr *) &servaddr,len);
	}

	if (c=='r') {
		char buffer[1024];
		len = sizeof(servaddr); //len is value/resuslt
		n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				0, ( struct sockaddr *) &servaddr,
				&len);
		buffer[n] = '\0';
		printf("%s\n",buffer);
		}
	}

}