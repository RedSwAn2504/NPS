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

void func(int sockfd)
{
    char buff[80];
    int n;
    while (1)
    {
        n = 0;
        printf("From Client : ");
        recv(sockfd, buff, sizeof(buff), 0);
        printf("%s\n", buff);
        bzero(buff, sizeof(buff));

        printf("To Client : ");
        while ((buff[n++] = getchar()) != '\n')
            ;
        send(sockfd, buff, sizeof(buff), 0);
        exit(0);
    }
}

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv, cli;
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(8080);

    bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));

    listen(sockfd, 5);

    u_int len = sizeof(struct sockaddr_in);
    int connfd = accept(sockfd, (struct sockaddr *)&cli, &len);

    func(connfd);

    close(sockfd);
}