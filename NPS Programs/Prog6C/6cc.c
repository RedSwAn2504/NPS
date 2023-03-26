#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <arpa/inet.h>

void str_echo(FILE *fp, int sockfd, struct sockaddr *serv, int len)
{
    int n = 1024, cont;
    char *buff = malloc(n);
    while (fgets(buff, n, fp) != NULL)
    {
        sendto(sockfd, buff, n, 0, serv, len);
        if ((cont = recvfrom(sockfd, buff, n, 0, serv, &len)) > 0)
            fputs(buff, stdout);
    }
    printf("\nEOF\n");
}

int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv.sin_port = htons(8080);

    str_echo(stdin, sockfd, (struct sockaddr *)&serv, sizeof(struct sockaddr_in));

    close(sockfd);
}