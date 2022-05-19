// Client side implementation of UDP client-server model
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
	char *hello = "Hello from client";
	struct sockaddr_in	 servaddr;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
	int n, len;
	
	// sendto(sockfd, (const char *)hello, strlen(hello),
	// 	0, (const struct sockaddr *) &servaddr,
	// 		sizeof(servaddr));
	// printf("Hello message sent.\n");
		
	// n = recvfrom(sockfd, (char *)buffer, MAXLINE,
	// 			0, (struct sockaddr *) &servaddr,
	// 			&len);
	// buffer[n] = '\0';
	// printf("Server : %s\n", buffer);

	int x,y;
	int sum;
	printf("Enter 2 no");
	scanf("%d%d",&x,&y);
	sendto(sockfd,&x,4,0,(const struct sockaddr*)&servaddr,sizeof(servaddr));
	sendto(sockfd,&y,4,0,(const struct sockaddr*)&servaddr,sizeof(servaddr));
	// printf("sent");
	recvfrom(sockfd,&sum,4,0,(struct sockaddr*)&servaddr,&len);

	printf("sum= %d\n",sum);
	close(sockfd);
	return 0;
}

