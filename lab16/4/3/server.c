#include <err.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <linux/ip.h>
#include <linux/udp.h> 
#include <net/if.h>  
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
    struct sockaddr_ll serv;
    int raw_sock_fd;
    char msg_recv[STR_SIZE_MAX] = {0};
    socklen_t len = sizeof(struct sockaddr_ll);

    memset(&serv, 0, sizeof(serv));
    serv.sll_family = AF_PACKET;
    serv.sll_protocol = htons(ETH_P_ALL);
    serv.sll_ifindex = if_nametoindex("enp0s8");

    printf("Запуск сервера...\n");

    CHECK_ERROR(raw_sock_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL)), "socket");
    printf("Raw сокет создан.\n");
    CHECK_ERROR(bind(raw_sock_fd, (struct sockaddr *)&serv, len), "bind");
    printf("Raw сокет привязан.\n");

    CHECK_ERROR(recvfrom(raw_sock_fd, msg_recv, STR_SIZE_MAX, 0, (struct sockaddr *)&serv, &len), "recvfrom");
    printf("Сообщение получено.\n");

    struct ethhdr *eth_header = (struct ethhdr *)msg_recv;
    struct iphdr *ip_header = (struct iphdr *)(msg_recv + sizeof(struct ethhdr));
    struct udphdr *udp_header = (struct udphdr *)(msg_recv + sizeof(struct ethhdr) + sizeof(struct iphdr));

    if (ip_header->protocol == IPPROTO_UDP && ntohs(udp_header->dest) == PORT_SERVER) {
        printf("Отправлено: %s\n", msg_recv + sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct udphdr));
    }

    CHECK_ERROR(sendto(raw_sock_fd, msg_recv, STR_SIZE_MAX, 0, (struct sockaddr *)&serv, len), "sendto");
    printf("Сообщение отправлено обратно клиенту.\n");

    CHECK_ERROR(close(raw_sock_fd), "close");
    printf("Raw сокет закрыт.\n");

    return 0;
}