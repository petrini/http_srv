#include <stdio.h>
#include <stdlib.h>

#include "tcp.h"

#define STATUS_SUCCESS 1
#define STATUS_ERROR 0

int main(int argc, char *argv[])
{
    if(argc != 1)
    {
        printf("Usage: %s\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    tcp_server server = {0};
    server_status_e status = bind_tcp_port(&server, 8080);
    if(status != SERVER_OK)
    {
        fprintf(stderr, "Server initialization failed\n");
        exit(EXIT_FAILURE);
    }

    int client_fd = accept_client(server.socket_fd);
    if(client_fd == STATUS_ERROR)
    {
        fprintf(stderr, "Failed to accept client connection\n");
        close(server.socket_fd);
        exit(EXIT_FAILURE);
    }

    printf("Client connected\n");

    close(client_fd);
    close(server.socket_fd);

    return STATUS_SUCCESS;
}

