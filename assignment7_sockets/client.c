//#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    // 1.) socket

    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1)
    {
        perror("socket");
        exit(-1);
    }

    // 2.) connect
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);

    char *ip_address = "127.0.0.1";
    inet_pton(AF_INET, ip_address, &addr.sin_addr);

    printf("Connecting to server\n");
    int connect_result = connect(client_fd, (struct sockaddr *)&addr, sizeof(addr));
    if (connect_result == -1)
    {
        perror("connect");
        exit(-1);
    }
    
    char buf[1024] = {0};
    strcpy(buf,"hello");
    printf("Msg to send: %s\n", buf);
    send(client_fd, buf, strlen(buf), 0);
    
    strcpy(buf,"");  // clear the buffer
    read(client_fd, buf, sizeof(buf) - 1);
    printf("Server responded with: %s\n\n", buf);

    memset(buf, 0, sizeof(buf)); // clear the buffer
    strcpy(buf,"exit");
    printf("Msg to send: %s\n", buf);
    send(client_fd, buf, strlen(buf), 0);
    //char buf[1024] = {0};
    memset(buf, 0, sizeof(buf)); // clear the buffer
    read(client_fd, buf, sizeof(buf) - 1);
    printf("Server responded with: %s\n", buf);
    
    printf("closing connection\n");
    close(client_fd);
}