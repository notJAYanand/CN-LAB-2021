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
#define MAXLINE  1024
#define OUT      0
#define IN       1

int countWords(char *str)
{
    int flag =0;
    int word_count = 0;  // word count
 
    while (*str)
    {
        // ye sab character hai to flag 0
        
        if (*str == ' ' || *str == '\n' || *str == '\t')
            flag =0;
        // flag agar 0 hai to 1 kar do agar space hua to upar phir 0 ho jaayega
        else if (flag ==0)
        {
            flag = 1;
            ++word_count;
        }
        //agla word
        ++str;
    }
 
    return word_count;
}

// Driver code
int main() {
	int sockfd;
	char buffer[MAXLINE];
	// char *hello = "Hello from server";
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
	
	int len, n, count=0;

	len = sizeof(cliaddr); //len is value/resuslt

	n = recvfrom(sockfd, (char *)buffer, MAXLINE, 0, ( struct sockaddr *) &cliaddr, &len);
	buffer[n] = '\0';

	printf("Client input: %s\n", buffer);
    count = countWords(buffer);

    sendto(sockfd, &count, sizeof(count), 0, (const struct sockaddr *) &cliaddr, len);
	
    printf("RESULT SENT TO CLIENT\n");
	
	return 0;
}