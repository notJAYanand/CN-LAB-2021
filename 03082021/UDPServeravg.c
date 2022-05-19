// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT	 8080
#define MAXLINE 1024

// Driver code
int main() {
	int sockfd;
	char buffer[MAXLINE];
	char *hello = "Hello from server";
	struct sockaddr_in servaddr, cliaddr;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	
	int len, n;

	len = sizeof(cliaddr); //len is value/resuslt

	// n = recvfrom(sockfd, (char *)buffer, MAXLINE,
	// 			0, ( struct sockaddr *) &cliaddr,
	// 			&len);
	// buffer[n] = '\0';
	// printf("Client : %s\n", buffer);
	// sendto(sockfd, (const char *)hello, strlen(hello),
	// 	0, (const struct sockaddr *) &cliaddr,
	// 		len);
	// printf("Hello message sent.\n");
	int a[5];
    float sum=0;int i;
	
    recvfrom(sockfd,a,sizeof(a),0, ( struct sockaddr *)&cliaddr,&len );        

	for(int i = 0; i < 5; i++)
    {
        sum=sum+a[i];
        
    }
	
	// recvfrom(sockfd,&y,4,0, ( struct sockaddr *)&cliaddr,&len );
    float avg=0;
    avg=sum/5;
	// int sum=x+y;
	sendto(sockfd,&avg,sizeof(a),0, ( struct sockaddr *)&cliaddr,len);
	printf("RESULT SENT TO CLIENT\n");
	return 0;
}