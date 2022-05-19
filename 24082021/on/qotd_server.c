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

    char qotds[5][100] = {"tit for tat", "hello there", "whats up", "coding is cool", "spiderman"};

    printf("enter the protocol (udp/tcp) : ");
    scanf("%s", protocol_choice);
    printf("enter the port to bind :");
    scanf("%d", &port);

    if (strcmp(protocol_choice, "udp") == 0)
    {
        char buffer[8];
        int sockfd;
        char *invalid = "invalid Request";

        struct sockaddr_in servaddr, cliaddr;
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
        servaddr.sin_port = htons(port);

        // Bind the socket with the server address
        if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }

        while (1)
        {
            int random_number;
            random_number = rand() % 5;
            int n, len;
            len = sizeof(cliaddr);
            n = recvfrom(sockfd, buffer, 8, 0, (struct sockaddr *)&cliaddr, &len);
            buffer[n] = '\0';
            if (strcmp(buffer, "qotd") == 0)
            {
                sendto(sockfd, qotds[random_number], strlen(qotds[random_number]), 0, (const struct sockaddr *)&cliaddr, len);
            }
            else
            {
                sendto(sockfd, invalid, strlen(invalid), 0, (const struct sockaddr *)&cliaddr, len);
            }
        }
    }
    else if (strcmp(protocol_choice, "tcp") == 0)
    {
        char buffer[8];
        int sockfd;
        char *invalid = "invalid Request";
        struct sockaddr_in servaddr, cliaddr;

        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }

        memset(&servaddr, 0, sizeof(servaddr));
        memset(&cliaddr, 0, sizeof(cliaddr));

        // Filling server information
        servaddr.sin_family = AF_INET; // IPv4
        servaddr.sin_addr.s_addr = INADDR_ANY;
        servaddr.sin_port = htons(port);

        // Bind the socket with the server address
        if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
        if (listen(sockfd, 3) < 0)
        {
            perror("error while listen");
            exit(EXIT_FAILURE);
        }

        while (1)
        {
            int random_number;
            random_number = rand() % 5;

            int n, len, new_sock;
            len = sizeof(cliaddr);

            if ((new_sock = accept(sockfd, (struct sockaddr *)&cliaddr,
                                   (socklen_t *)&len)) < 0)
            {
                printf("error while connecting");
                exit(EXIT_FAILURE);
            }

            n = read(new_sock, buffer, 8);
            buffer[n] = '\0';

            printf("%s", buffer);
            printf("abcd");
            if (strcmp(buffer, "qotd") == 0)
            {
                send(new_sock, qotds[random_number], strlen(qotds[random_number]), 0);
            }
            else
            {
                send(new_sock, invalid, strlen(invalid), 0);
            }
        }
    }
    else
    {
        printf("the protocol is not supported ");
        exit(EXIT_FAILURE);
    }
}