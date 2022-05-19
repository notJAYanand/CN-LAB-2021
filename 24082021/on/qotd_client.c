#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main()
{
    char protocol_choice[4];
    int port;
    printf("enter the protocol (udp/tcp) : ");
    scanf("%s", protocol_choice);
    printf("enter the port to bind :");
    scanf("%d", &port);

    if (strcmp(protocol_choice, "udp") == 0)
    {
        char buffer[100];
        int sockfd;
        char *request = "qotd";
        struct sockaddr_in servaddr;
        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }
        memset(&servaddr, 0, sizeof(servaddr));

        // Filling server information
        servaddr.sin_family = AF_INET; // IPv4
        servaddr.sin_addr.s_addr = INADDR_ANY;
        servaddr.sin_port = htons(port);

        sendto(sockfd, request, strlen(request),
               0, (const struct sockaddr *)&servaddr,
               sizeof(servaddr));

        int n, len;
        len = sizeof(servaddr);
        n = recvfrom(sockfd, buffer, 100, 0, (struct sockaddr *)&servaddr, &len);
        buffer[n] = '\0';
        printf("%s \n", buffer);
    }
    else if (strcmp(protocol_choice, "tcp") == 0)
    {
        char buffer[100];
        int sockfd;
        char *request = "qotd";
        struct sockaddr_in servaddr;
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }
        memset(&servaddr, 0, sizeof(servaddr));

        // Filling server information
        servaddr.sin_family = AF_INET; // IPv4
        servaddr.sin_addr.s_addr = INADDR_ANY;
        servaddr.sin_port = htons(port);

        if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        {
            printf("\nConnection Failed \n");
            exit(EXIT_FAILURE);
        }
        int n;

        send(sockfd, request, strlen(request), 0);
        n = read(sockfd, buffer, 100);
        buffer[n] = '\0';
        printf("%s \n", buffer);
        close(sockfd);
    }
    else
    {
        printf("the protocol is not supported ");
        exit(EXIT_FAILURE);
    }
}