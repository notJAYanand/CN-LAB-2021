// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <math.h>

#define PORT 4040
#define MAXLINE 1024

// Driver code
int main()
{
    int sockfd;
    char buffer[MAXLINE];

    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
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
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;

    len = sizeof(cliaddr); //len is value/resuslt
    int x;
    char *decision;
    recvfrom(sockfd, &x, 4, 0, (struct sockaddr *)&cliaddr, &len);

    int num = 0, digits, sum = 0;
    //digits = (int) log10(n);
    int r;
    while (x > 0)
    {
        r = x % 10;
        sum = sum * 10 + r;
        x = x / 10;
    }
    x = sum;



    char *zero="zero ";
    char *one="one ";
    char *two="two ";
    char *three="three ";
    char *four="four ";
    char *five="five ";
    char *six="six ";
    char *seven="seven ";
    char *eight="eight ";
    char *nine="nine ";


    while (x >0)
    {
        r = x % 10;
        switch (r)
        {
        case 1:
        
        sendto(sockfd, one, strlen(one), 0, (const struct sockaddr *)&cliaddr, len);
            break;
        case 2:
            sendto(sockfd, two, strlen(two), 0, (const struct sockaddr *)&cliaddr, len);
            break;
        case 3:
            sendto(sockfd, three, strlen(three), 0, (const struct sockaddr *)&cliaddr, len);
            break;
        case 4:
            sendto(sockfd, four, strlen(four), 0, (const struct sockaddr *)&cliaddr, len);
            break;
        case 5:
            sendto(sockfd, five, strlen(five), 0, (const struct sockaddr *)&cliaddr, len);
            break;
        case 6:
            sendto(sockfd, six, strlen(six), 0, (const struct sockaddr *)&cliaddr, len);
            break;
        case 7:
            sendto(sockfd, seven, strlen(seven), 0, (const struct sockaddr *)&cliaddr, len);
            break;
        case 8:
            sendto(sockfd, eight, strlen(eight), 0, (const struct sockaddr *)&cliaddr, len);
            break;
        case 9:
            sendto(sockfd, nine, strlen(nine), 0, (const struct sockaddr *)&cliaddr, len);
            break;
        case 0:
            sendto(sockfd, zero, strlen(zero), 0, (const struct sockaddr *)&cliaddr, len);
            break;
        default:
            printf("error");
            break;
        }
        x = x / 10;

    }
    return 0;


sendto(sockfd, (const char *)decision, strlen(decision), 0, (const struct sockaddr *)&cliaddr, len);
printf("RESULT SENT TO CLIENT\n");
return 0;
}