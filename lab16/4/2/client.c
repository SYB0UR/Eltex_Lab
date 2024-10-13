

#include <arpa/inet.h>
#include <err.h>
#include <linux/ip.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define STR_SIZE_MAX 255
#define PORT_CLIENT 7777
#define PORT_SERVER 12345

#define CHECK_ERROR(err_n, err_str) \
    if ((err_n) < 0) { perror(err_str); exit(EXIT_FAILURE); }

unsigned short checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum = 0;
    unsigned short result;
    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;
    if (len == 1)
        sum += *(unsigned char*)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

int main() {
    struct udphdr udp_header;
    struct iphdr ip_header;
    struct sockaddr_in serv;
    int raw_sock_fd, socket_option = 1;
    char *msg_send = "Hello!", udp_msg[STR_SIZE_MAX] = {0}, msg_recv[STR_SIZE_MAX] = {0};
    socklen_t struct_sock_length = sizeof(serv);

    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT_SERVER); 
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    ip_header.version = 4;
    ip_header.ihl = 5;
    ip_header.tos = 0;
    ip_header.tot_len = htons(sizeof(struct iphdr) + sizeof(struct udphdr) + strlen(msg_send));
    ip_header.id = htons(54321);
    ip_header.frag_off = 0;
    ip_header.ttl = 64;
    ip_header.protocol = IPPROTO_UDP;
    ip_header.check = 0;
    ip_header.saddr = inet_addr("127.0.0.1");
    ip_header.daddr = inet_addr("127.0.0.1");
    ip_header.check = checksum((unsigned short *)&ip_header, sizeof(ip_header));

    udp_header.source = htons(PORT_CLIENT);
    udp_header.dest = htons(PORT_SERVER);
    udp_header.len = htons(sizeof(udp_header) + strlen(msg_send));
    udp_header.check = 0;

    memcpy(udp_msg, &ip_header, sizeof(ip_header));
    memcpy(udp_msg + sizeof(ip_header), &udp_header, sizeof(udp_header));
    memcpy(udp_msg + sizeof(ip_header) + sizeof(udp_header), msg_send, strlen(msg_send));

    CHECK_ERROR(raw_sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP), "socket");
    CHECK_ERROR(setsockopt(raw_sock_fd, IPPROTO_IP, IP_HDRINCL, &socket_option, sizeof(socket_option)), "setsockopt");

    CHECK_ERROR(sendto(raw_sock_fd, udp_msg, sizeof(ip_header) + sizeof(udp_header) + strlen(msg_send), 0, (struct sockaddr *)&serv, struct_sock_length), "sendto");

    while (1) {
        CHECK_ERROR(recvfrom(raw_sock_fd, msg_recv, STR_SIZE_MAX, 0, (struct sockaddr *)&serv, &struct_sock_length), "recvfrom");
        struct iphdr *ip_header_recv = (struct iphdr *)msg_recv;
        struct udphdr *udp_header_recv = (struct udphdr *)(msg_recv + ip_header_recv->ihl * 4);
        if (ntohs(udp_header_recv->dest) == PORT_CLIENT) {
            break;
        }
    }

    printf("Принято: %s\n", msg_recv + sizeof(struct iphdr) + sizeof(struct udphdr));

    close(raw_sock_fd);
    return 0;
}
