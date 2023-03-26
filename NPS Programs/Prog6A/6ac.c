#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void str_echo(FILE *fp, int sockfd)
{
    int n = 1024, cont;
    char *buff = malloc(n);
    while (fgets(buff, n, fp) != NULL)
    {
        send(sockfd, buff, n, 0);

        if ((cont = recv(sockfd, buff, n, 0)) > 0)
            fputs(buff, stdout);
    }
    printf("\nEOF\n");
}

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv.sin_port = htons(8080);

    connect(sockfd, (struct sockaddr *)&serv, sizeof(serv));

    str_echo(stdin, sockfd);

    close(sockfd);
}