// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 4040
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
    char *line;
    int x;

    printf("Enter Number : ");
    scanf("%d", &x);
    sendto(sockfd, &x, 4, 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    //printf("Number Sent to Server for Checking\n\n");
    int t=x;
    while(t>0)
    {
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, 0, (struct sockaddr *)&servaddr,&len);

    buffer[n] = '\0';
    printf( "%s ", buffer);
    
    t=t/10;
    }
        
        
    
    
    printf("and my roll number is 1905089\n\n");

    close(sockfd);
    return 0;
}