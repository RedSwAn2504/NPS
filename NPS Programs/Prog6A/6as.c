#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void str_echo(int connfd)
{
    int n = 1024, cont;
    char *buff = malloc(n);
    while (1)
    {
        if ((cont = recv(connfd, buff, n, 0)) > 0)
            send(connfd, buff, cont, 0);
    }
}

int main()
{
    int sockfd, connfd, n, pid;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv, cli;
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(8080);

    bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));

    listen(sockfd, 3);

    while (1)
    {
        n = sizeof(struct sockaddr_in);
        connfd = accept(sockfd, (struct sockaddr *)&cli, &n);
        if ((pid = fork()) == 0)
        {
            close(sockfd);
            str_echo(connfd);
            exit(0);
        }
        close(connfd);
    }
}