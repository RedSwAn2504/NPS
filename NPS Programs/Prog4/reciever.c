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
    int sockfd, len;
    char buff[1024];

    struct sockaddr_in recv;
    struct ip_mreq req;

    int yes = 1;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &yes, sizeof(yes));

    recv.sin_family = AF_INET;
    recv.sin_addr.s_addr = INADDR_ANY;
    recv.sin_port = htons(12345);

    bind(sockfd, (struct sockaddr *)&recv, sizeof(recv));

    req.imr_multiaddr.s_addr = inet_addr("225.0.0.37");
    req.imr_interface.s_addr = INADDR_ANY;

    setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &req, sizeof(req));

    while (1)
    {
        len = sizeof(recv);
        recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr *)&recv, &len);

        puts(buff);
    }
}