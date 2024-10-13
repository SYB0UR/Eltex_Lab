#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/tcp_local_socket"

int main() {
    int server_fd, client_fd;
    struct sockaddr_un address;
    char buffer[256];
    socklen_t addr_len = sizeof(address);

    if ((server_fd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&address, 0, sizeof(address));
    address.sun_family = AF_LOCAL;
    strncpy(address.sun_path, SOCKET_PATH, sizeof(address.sun_path) - 1);

    unlink(SOCKET_PATH);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if ((client_fd = accept(server_fd, (struct sockaddr *)&address, &addr_len)) < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    read(client_fd, buffer, sizeof(buffer));
    printf("Received: %s\n", buffer);
    close(client_fd);
    close(server_fd);
    return 0;
}
