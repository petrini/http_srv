#include <stdio.h>
#include <string.h>

#include "tcp.h"

#define STATUS_SUCCESS 1
#define STATUS_ERROR 0

server_status_e bind_tcp_port(tcp_server *server, int port)
{
    memset(server, 0, sizeof(*server));
    server->socket_fd = socket(AF_INET, SOCK_STREAM, SOCKET_PROTOCOL);
    if(server->socket_fd < 0)
    {
        perror("socket");
        return SERVER_SOCKET_ERROR;
    }

    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(port);

    if(bind(server->socket_fd, (struct sockaddr *)&server->address, sizeof(server->address)) < 0)
    {
        perror("bind");
        close(server->socket_fd);
        return SERVER_LISTEN_ERROR;
    }

    if(listen(server->socket_fd, LISTEN_BACKLOG) < 0)
    {
        perror("listen");
        close(server->socket_fd);
        return SERVER_LISTEN_ERROR;
    }

    printf("Server bound and listening\n");

    return SERVER_OK;
}

int accept_client(int server_fd)
{
    struct sockaddr_in client_address = {0};
    socklen_t client_len = sizeof(client_address);

    int client_fd = accept(server_fd, (struct sockaddr *)&client_address, &client_len);
    if(client_fd < 0)
    {
        perror("accept");
        return STATUS_ERROR;
    }

    return client_fd;
}

