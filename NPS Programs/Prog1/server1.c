#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <string.h>

void func(int connfd)
{
    char buff[80];
    int n;
    while (1)
    {
        printf("From Client : ");
        recv(connfd, buff, sizeof(buff), 0);
        printf("%s\n", buff);
        bzero(buff, sizeof(buff));

        n = 0;
        printf("To Client : ");
        while ((buff[n++] = getchar()) != '\n')
            ;
        send(connfd, buff, sizeof(buff), 0);
        printf("\n");
        bzero(buff, sizeof(buff));
    }
}

int main()
{
    int sockfd, len, connfd;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv, cli;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8080);
    serv.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));

    listen(sockfd, 5);

    len = sizeof(struct sockaddr_in);

    connfd = accept(sockfd, (struct sockaddr *)&cli, &len);

    func(connfd);

    close(sockfd);
}