#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/udp_local_socket"

int main() {
    int sockfd;
    struct sockaddr_un server_addr;
    char *message = "Hello, Server!";

    if ((sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_LOCAL;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    sendto(sockfd, message, strlen(message) + 1, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

    close(sockfd);
    return 0;
}
