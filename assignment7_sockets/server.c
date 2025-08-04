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

    // 1.) Socket

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        perror("socket");
        exit(-1);
    }

    // 2.) bind

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8080);

    int bind_result = bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    if (bind_result == -1)
    {
        perror("bind");
        exit(-1);
    }

    // 3.) listen
    int listen_result = listen(server_fd, 1);
    if (listen_result == -1)
    {
        perror("listen");
        exit(-1);
    }

    // 4.) accept
    int addrlen = sizeof(addr);
    printf("Waiting for client to connect\n");
    int client_fd = accept(server_fd, (struct sockaddr *)&addr, &addrlen);
    if (client_fd == -1)
    {
        perror("accept");
        exit(-1);
    }

    printf("connected to client\n");

    // 5.) connect
    char buf[1024] = {0};
    read(client_fd, buf, sizeof(buf) - 1);
    printf("Msg received from client: %s\n", buf);
    strcpy(buf,"world");
    printf("Responding with: %s\n\n", buf);
    send(client_fd, "world", strlen("world"), 0);

    strcpy(buf,"");  // clear the buffer
    read(client_fd, buf, sizeof(buf) - 1);
    printf("Msg received from client: %s\n", buf);

    strcpy(buf,"exit");
    printf("Responding with: %s\n", buf);
    send(client_fd, buf, strlen(buf), 0);
    printf("closing connection\n");

    close(server_fd);
    close(client_fd);

    return 0;
}