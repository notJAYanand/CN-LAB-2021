#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8081
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *yes = "armstrong number";
	 char *no = "NOT armstrong number";


    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
	
    int x,sum=0;
    read(new_socket, &x, sizeof(x));
    int n=x;
    while(x!=0)
	{
        int r=x%10;
        sum=sum+(r*r*r);
        x=x/10;		                                               
    }
	if(sum==n)
	{
        send(new_socket, yes, strlen(yes), 0);
    }
	else
	{
        send(new_socket, no, strlen(no), 0);
        }
    close(new_socket); // closes this particular connection
    close(server_fd); // server cannot accept any more connections
    return 0;
}