#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 4444
struct calc
{
    int a;
    int b;
    char op;
} calc;
int main(int argc, char const *argv[])
{

    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    calc.a = 33;
    calc.b = 3;
    calc.op = '/';
    int result;
    send(sock, &calc, sizeof(calc), 0);
    printf("\nNumbers sent to the server for operation\n");
    valread = read(sock, &result, sizeof(result));
    printf("\nresult :%d\n", result);

    return 0;
}