#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void str_echo(int connfd1, int connfd2)
{
    int cont, n = 1024;
    char *buff = malloc(n);
    while (1)
    {
        if ((cont = recv(connfd1, buff, n, 0)) > 0)
        {
            send(connfd2, buff, cont, 0);
            cont = recv(connfd2, buff, n, 0);
            send(connfd1, buff, cont, 0);
        }
        else
        {
            cont = recv(connfd2, buff, n, 0);
            send(connfd1, buff, cont, 0);
            cont = recv(connfd1, buff, n, 0);
            send(connfd2, buff, cont, 0);
        }
    }
}

int main()
{
    int sockfd, connfd1, connfd2;

    // Intialise the socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Initialise the socket structure
    struct sockaddr_in serv, cli;
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(8080);

    // Bind the socket to the port
    bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));

    // Listen to the incoming requests
    listen(sockfd, 5);

    // Accepting the new requests
    int len = sizeof(struct sockaddr_in);
    connfd1 = accept(sockfd, (struct sockaddr *)&cli, &len);
    connfd2 = accept(sockfd, (struct sockaddr *)&cli, &len);
    int pid;
    if ((pid = fork()) == 0) // for concurrent clients to be proccessed
    {
        close(sockfd);
        str_echo(connfd1, connfd2);
        exit(0);
    }
    close(connfd1);
    close(connfd2);
}