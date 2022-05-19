#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT	 8080

struct student
{
    int id;
    char *name;
}student;

// Driver code
int main() {
	int sockfd;
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
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	
	int len, n, num, remainder, reversed_id = 0;

	len = sizeof(cliaddr); //len is value/resuslt

    recvfrom(sockfd, &student, sizeof(student), 0, ( struct sockaddr *) &cliaddr, &len);

    num = student.id;
    while (num != 0) {
        remainder = num % 10;
        reversed_id = reversed_id * 10 + remainder;
        num /= 10;
    }

    student.id = reversed_id;

	//printf("Reverse %d\n", reversed_id);
	sendto(sockfd, &reversed_id, sizeof(student), 0, (const struct sockaddr *) &cliaddr, len);
	printf("RESULT SENT TO CLIENT\n");
	
	return 0;
}