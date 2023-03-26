#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <arpa/inet.h>

void str_echo(int sockfd, struct sockaddr *cli, int len)
{
    int n = 1024, cont;
    char *buff = malloc(n);
    while (1)
    {
        cont = recvfrom(sockfd, buff, n, 0, cli, &len);
        sendto(sockfd, buff, cont, 0, cli, len);
    }
}

int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in serv, cli;
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(1900);

    bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));

    str_echo(sockfd, (struct sockaddr *)&cli, sizeof(struct sockaddr_in));

    close(sockfd);
}