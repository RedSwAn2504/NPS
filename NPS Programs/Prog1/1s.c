#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void func(int sockfd)
{
    char buff[80];
    int n;
    while (1)
    {
        // receive from client
        n = 0;
        printf("From Client : ");
        recv(sockfd, buff, sizeof(buff), 0);
        printf("%s\n", buff);

        // empty the buffer
        bzero(buff, sizeof(buff));

        // send msg to client
        printf("To Client :\n");
        while ((buff[n++] = getchar()) != '\n')
            ;
        send(sockfd, buff, sizeof(buff), 0);
        bzero(buff, sizeof(buff));
        if (strncmp(buff, "exit", 4) == 0)
        {
            printf("Client exit\n");
            exit(0);
        }

        // now empty the buffer after sending
    }
}

int main()
{
    // Initialize the socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Intialize the environment for sockaddr structure
    struct sockaddr_in srv;
    srv.sin_family = AF_INET;
    srv.sin_port = htons(8080);
    srv.sin_addr.s_addr = INADDR_ANY;

    // bind the socket to local port
    bind(sockfd, (struct sockaddr *)&srv, sizeof(srv));

    // Listen the requests from client
    listen(sockfd, 5);

    // Accepting the new request from client
    struct sockaddr_in cli;
    u_int len = sizeof(cli);
    int connfd = accept(sockfd, (struct sockaddr *)&cli, &len);

    // Handle the new request
    func(connfd);

    // Close the socket
    close(sockfd);
}