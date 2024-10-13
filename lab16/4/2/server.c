#include <arpa/inet.h>
#include <err.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define STR_SIZE_MAX 255
#define PORT_SERVER 12345

#define CHECK_ERROR(err_n, err_str) \
    if ((err_n) < 0) { perror(err_str); exit(EXIT_FAILURE); }

int main() {
    struct sockaddr_in serv, client;
    int sock_fd;
    char msg_recv[STR_SIZE_MAX] = {0};
    socklen_t len = sizeof(struct sockaddr);

    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT_SERVER);
    serv.sin_addr.s_addr = INADDR_ANY;

    CHECK_ERROR(sock_fd = socket(AF_INET, SOCK_DGRAM, 0), "socket");
    CHECK_ERROR(bind(sock_fd, (struct sockaddr *)&serv, len), "bind");

    CHECK_ERROR(recvfrom(sock_fd, msg_recv, STR_SIZE_MAX, 0, (struct sockaddr *)&client, &len), "recvfrom");
    printf("Отправлено: %s\n", msg_recv);

    CHECK_ERROR(sendto(sock_fd, msg_recv, STR_SIZE_MAX, 0, (struct sockaddr *)&client, len), "sendto");

    CHECK_ERROR(close(sock_fd), "close");
    return 0;
}
