// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 1024

// Driver code
int main()
{
    int sockfd;
    char buffer[MAXLINE];
    char *hello;
    struct sockaddr_in servaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n, len;

    int x;

    printf("Enter Number : ");
    scanf("%d", &x);
    sendto(sockfd, &x, 4, 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("Number Sent to Server for Checking\n\n");
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, 0, (struct sockaddr *)&servaddr,&len);
    buffer[n] = '\0';
    printf("Is it a factorial of numbers between 1 and 7 ? %s\n", buffer);

    close(sockfd);
    return 0;
}
