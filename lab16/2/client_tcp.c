#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *hello = "Привет, сервер!";
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    send(sock, hello, strlen(hello), 0);
    printf("Приветствие отправлено\n");
    read(sock, buffer, 1024);
    printf("Ответ от сервера: %s\n", buffer);

    for (int i = 1; i <= 10; i++) {
        char message[16];
        snprintf(message, sizeof(message), "%d", i);
        send(sock, message, strlen(message), 0);
        printf("Отправлено: %d\n", i);
        sleep(1);
    }

    close(sock);
    return 0;
}
