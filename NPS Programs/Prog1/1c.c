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
    char buff[100];
    int n;
    while (1)
    {
        // send somthing to server
        printf("To server\n");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        send(sockfd, buff, sizeof(buff), 0);

        // empty the buffer
        bzero(buff, sizeof(buff));

        // recieve from server
        recv(sockfd, buff, sizeof(buff), 0);
        printf("From server : %s\n", buff);
        if (strncmp(buff, "exit", 4) == 0)
        {
            printf("Server exit\n");
            exit(0);
        }

        // empty the buffer after recieving
        bzero(buff, sizeof(buff));
    }
}

int main()
{
    int sockfd;

    // Initialize socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Intialize sockaddr structure
    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv.sin_port = htons(8080);

    // Connect to server socket
    connect(sockfd, (struct sockaddr *)&serv, sizeof(serv));

    // Create a function to send messages
    func(sockfd);

    // Close the socket
    close(sockfd);
}