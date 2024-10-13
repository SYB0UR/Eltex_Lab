#include <err.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define STR_SIZE_MAX 255
#define PORT_SERVER 12345

static void CheckError(int err_n, char *err_str, int line) {
    if (err_n < 0) {
        err(EXIT_FAILURE, "%s: %d", err_str, line);
    }
}

void reverse(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

int main() {
    struct sockaddr_in serv, client;
    int sock_fd;
    char msg_recv[STR_SIZE_MAX] = {0};
    socklen_t len = sizeof(struct sockaddr);

    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT_SERVER);
    serv.sin_addr.s_addr = INADDR_ANY;

    CheckError(sock_fd = socket(AF_INET, SOCK_DGRAM, 0), "socket", __LINE__);
    CheckError(bind(sock_fd, (struct sockaddr *)&serv, len), "bind", __LINE__);

    CheckError(recvfrom(sock_fd, msg_recv, STR_SIZE_MAX, 0, (struct sockaddr *)&client, &len), "recvfrom", __LINE__);
    CheckError(printf("Отправлено: %s\n", msg_recv), "printf", __LINE__);

    reverse(msg_recv);
    CheckError(printf("Перевернутое сообщение: %s\n", msg_recv), "printf", __LINE__); 

    CheckError(sendto(sock_fd, msg_recv, STR_SIZE_MAX, 0, (struct sockaddr *)&client, len), "sendto", __LINE__);

    CheckError(close(sock_fd), "close", __LINE__);
    return 0;
}
