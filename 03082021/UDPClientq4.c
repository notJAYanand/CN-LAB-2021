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

struct student
{
    int id;
    char *name;
}student;


// Driver code
int main() {
	int sockfd;
	struct sockaddr_in	 servaddr;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
    
    student.id = 123;
    student.name = "jay";
	
    int n, len,a,b;

    sendto(sockfd, &student, sizeof(student), 0, (const struct sockaddr *) &servaddr, sizeof(servaddr));
	printf("VALUES SENT TO SERVER\n");

	struct student result;
	n = recvfrom(sockfd, &result, sizeof(result), 0, (struct sockaddr *) &servaddr, &len);
	printf("Reversed id= %d\n", result.id);

	close(sockfd);
	return 0;
}