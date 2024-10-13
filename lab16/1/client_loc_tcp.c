#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/tcp_local_socket"

int main() {
    int sockfd;
    struct sockaddr_un address;
    char *message = "Hello, Server!";

    if ((sockfd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&address, 0, sizeof(address));
    address.sun_family = AF_LOCAL;
    strncpy(address.sun_path, SOCKET_PATH, sizeof(address.sun_path) - 1);

    if (connect(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("connect");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    send(sockfd, message, strlen(message), 0);
    printf("Message sent\n");
    close(sockfd);
    return 0;
}
