#include <sys/types.h> /* See NOTES */
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
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
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
    int connect_result = connect(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    if (connect_result == -1)
    {
        perror("connect");
        exit(-1);
    }

    printf("Sending hello to server\n");
    send(server_fd, "hello", strlen("hello"), 0);
    char buf[1024] = {0};
    read(server_fd, buf, sizeof(buf) - 1);
    printf("Received: %s\n", buf);

    close(server_fd);
}