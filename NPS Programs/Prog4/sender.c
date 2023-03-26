#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in send;
    send.sin_family = AF_INET;
    send.sin_addr.s_addr = inet_addr("225.0.0.37");
    send.sin_port = htons(12345);

    char *msg = "RVCE";

    while (1)
    {
        sendto(sockfd, msg, sizeof(msg), 0, (struct sockaddr *)&send, sizeof(send));

        sleep(1);
    }
    close(sockfd);
}