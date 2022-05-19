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
    short port;

    char qotds[5][100] = {
        "tit for tat", "hello there", "whats up", "coding is cool", "spiderman"};
    printf("Enter protocol (udp/tcp): \n");
    scanf("%s", protocol_choice);

    printf("enter the port to bind to:\n");
    scanf("%hd", &port);

    if (strcmp(protocol_choice, "udp") == 0)
    {
        char buffer[8];
        char *invalid_message = "Invalid Request.";
        int sockfd;
        struct sockaddr_in servaddr, cliaddr;
        if(sockfd=socket(AF_INET, SOCK_STREAM, 0)<0)
        {
            printf("Socket creation Failed.");
            exit(EXIT_FAILURE);
        }

        //populate server address
        memset(&servaddr, 0, sizeof(servaddr));
        memset(&cliaddr, 0, sizeof(cliaddr));
        //bind socket
        servaddr.sin_family = AF_INET; // IPv4

        servaddr.sin_port = htons(port);
        servaddr.sin_addr.s_addr = INADDR_ANY;

        if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        {
            printf("bind failed");
            exit(EXIT_FAILURE);
        }
        //loop
        //recvfrm
        //check if"qotd"
        //sendto qotd else error
        while(1)
        {
            int rand_num = rand() % 5;
            int n, len;
            len = sizeof(cliaddr);
            n = recvfrom(sockfd, buffer, 8, 0, (struct sockaddr *)&cliaddr, &len);
            buffer[n] = '\0';

            if (strcmp(buffer, "qotd") == 0)
            {
                sendto(sockfd, qotds[rand_num], strlen(qotds[rand_num]), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
            }
            else
            {
                sendto(sockfd, invalid_message, strlen(invalid_message), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
            }
        }
    }
    else if (strcmp(protocol_choice, "tcp") == 0)
    {
        char buffer[8];
        char *invalid_message = "Invalid Request.";
        int sockfd;
        struct sockaddr_in servaddr, cliaddr;
        if(sockfd = socket(AF_INET, SOCK_STREAM, 0)<0)
        {
            printf("Socket creation Failed.");
            exit(EXIT_FAILURE);
        }

        //populate server address
        memset(&servaddr, 0, sizeof(servaddr));
        memset(&cliaddr, 0, sizeof(cliaddr));
        //bind socket
        servaddr.sin_family = AF_INET; // IPv4

        servaddr.sin_port = htons(port);
        servaddr.sin_addr.s_addr = INADDR_ANY;

        if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        {
            printf("bind failed");
            exit(EXIT_FAILURE);
        }

        if(listen(sockfd,3)<0)
        {
            printf("listening failed");
            exit(EXIT_FAILURE);
        }
        //loop
        //recvfrm
        //check if"qotd"
        //sendto qotd else error
        while(1)
        {
            int rand_num = rand() % 5;
            int n, len;
            int new_sock;
            len = sizeof(cliaddr);
            if((new_sock= connect(sockfd, (struct sockaddr *)&cliaddr,len))<0){
                printf("Error while connecting");
                exit(EXIT_FAILURE);
            }

            n = read(new_sock, buffer, 8);
            buffer[n] = '\0';

            if (strcmp(buffer, "qotd") == 0)
            {
                send(new_sock, qotds[rand_num],strlen(qotds[rand_num]),0);
            }
            else
            {
                send(new_sock, invalid_message,strlen(invalid_message),0);
            }
            close(new_sock);
        }
    }
    else
    {
        printf("protocol is not supported\n");
        exit(EXIT_FAILURE);
    }
}