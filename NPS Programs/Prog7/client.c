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

void func(int sockfd)
{
    int n;
    char buff[80];
    while (1)
    {
        printf("To Server : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        // scanf("%s", buff);
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