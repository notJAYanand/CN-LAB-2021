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

    printf("Enter protocol (udp/tcp): \n");
    scanf("%s", protocol_choice);

    printf("enter the server port:\n");
    scanf("%d", &port);
}