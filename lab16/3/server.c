#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MULTICAST_IP "224.0.0.1"
#define PORT 12345
#define MULTICAST_MESSAGE "This is a multicast message!"
#define BROADCAST_MESSAGE "This is a broadcast message!"

void send_multicast() {
    int sock;
    struct sockaddr_in multicast_addr;
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }

    memset(&multicast_addr, 0, sizeof(multicast_addr));
    multicast_addr.sin_family = AF_INET;
    multicast_addr.sin_addr.s_addr = inet_addr(MULTICAST_IP);
    multicast_addr.sin_port = htons(PORT);

    if (sendto(sock, MULTICAST_MESSAGE, strlen(MULTICAST_MESSAGE), 0, (struct sockaddr *)&multicast_addr, sizeof(multicast_addr)) < 0) {
        perror("sendto");
        exit(1);
    }
    printf("Multicast message sent.\n");
    close(sock);
}

void send_broadcast() {
    int sock;
    struct sockaddr_in broadcast_addr;
    int broadcast = 1;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }

    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0) {
        perror("setsockopt");
        exit(1);
    }

    memset(&broadcast_addr, 0, sizeof(broadcast_addr));
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_addr.s_addr = inet_addr("255.255.255.255");
    broadcast_addr.sin_port = htons(PORT);

    if (sendto(sock, BROADCAST_MESSAGE, strlen(BROADCAST_MESSAGE), 0, (struct sockaddr *)&broadcast_addr, sizeof(broadcast_addr)) < 0) {
        perror("sendto");
        exit(1);
    }
    printf("Broadcast message sent.\n");
    close(sock);
}

int main() {
    send_multicast();
    send_broadcast();
    return 0;
}
