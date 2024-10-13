#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define DEST_PORT 8081
#define DEST_IP "127.0.0.1"

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    char *message = "Привет, сервер!";
    char buffer[1024];

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(DEST_PORT);
    serv_addr.sin_addr.s_addr = inet_addr(DEST_IP);

    sendto(sock, message, strlen(message), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    printf("Сообщение отправлено\n");

    for (int i = 1; i <= 10; i++) {
        snprintf(buffer, sizeof(buffer), "Сообщение %d", i);
        sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
        printf("Отправлено: %s\n", buffer);
        sleep(1);
    }

    close(sock);
    return 0;
}
