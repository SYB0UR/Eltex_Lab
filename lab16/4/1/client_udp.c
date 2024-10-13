#include <err.h>
#include <linux/ip.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define STR_SIZE_MAX 255
#define PORT_CLIENT 7777
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
    struct udphdr udp_header;
    struct sockaddr_in serv;
    int raw_sock_fd;
    char *msg_send = "Hello!";
    char udp_msg[STR_SIZE_MAX] = {0};
    char msg_recv[STR_SIZE_MAX] = {0};
    socklen_t len = sizeof(struct sockaddr);
    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT_SERVER);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    CheckError(raw_sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP), "socket", __LINE__);

    udp_header.source = htons(PORT_CLIENT);
    udp_header.dest = htons(PORT_SERVER);
    udp_header.len = htons(8 + strlen(msg_send));
    udp_header.check = 0;

    memcpy(udp_msg, &udp_header, sizeof(udp_header));
    memcpy(udp_msg + sizeof(udp_header), msg_send, strlen(msg_send));

    CheckError(sendto(raw_sock_fd, udp_msg, sizeof(udp_header) + strlen(msg_send), 0, (struct sockaddr *)&serv, len), "send", __LINE__);

    while (1) {
        CheckError(recvfrom(raw_sock_fd, msg_recv, STR_SIZE_MAX, 0, (struct sockaddr *)&serv, &len), "recv", __LINE__);
        struct iphdr *ip_header = (struct iphdr *)msg_recv;
        struct udphdr *udp_header = (struct udphdr *)(msg_recv + (ip_header->ihl * 4));
        if (ntohs(udp_header->dest) == PORT_CLIENT)
            break;
    }

    printf("От сервера получено: %s\n", msg_recv + sizeof(struct iphdr) + sizeof(struct udphdr));
    reverse(msg_recv + sizeof(struct iphdr) + sizeof(struct udphdr));
    CheckError(printf("Принято: %s\n", msg_recv + sizeof(struct iphdr) + sizeof(struct udphdr)), "printf", __LINE__);
    CheckError(close(raw_sock_fd), "close", __LINE__);
    return 0;
}
