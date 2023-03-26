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
        printf("To server\n");
        while ((buff[n++] = getchar()) != '\n')
            ;
        send(sockfd, buff, sizeof(buff), 0);
    }
}

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv.sin_port = htons(8080);

    connect(sockfd, (struct sockaddr *)&serv, sizeof(serv));

    func(sockfd);

    close(sockfd);
}