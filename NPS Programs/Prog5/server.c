#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

void str_echo(int connfd1, int connfd2)
{
    int n = 1024, cont;
    char *buff = malloc(n);

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

int main()
{
    int sockfd, connfd1, connfd2, pid, n;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv, cli;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8080);
    serv.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));

    listen(sockfd, 5);

    n = sizeof(struct sockaddr_in);

    connfd1 = accept(sockfd, (struct sockaddr *)&cli, &n);
    connfd2 = accept(sockfd, (struct sockaddr *)&cli, &n);

    if ((pid = fork()) == 0)
    {
        close(sockfd);
        str_echo(connfd1, connfd2);
        exit(0);
    }
    close(connfd1);
    close(connfd2);
}