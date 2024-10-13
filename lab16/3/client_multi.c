#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MULTICAST_IP "224.0.0.1"
#define PORT 12345

void receive_multicast() {
    int sock;
    struct sockaddr_in addr;
    struct ip_mreq mreq;
    char buffer[1024];

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }

    int reuse = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        perror("setsockopt");
        exit(1);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);

    if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(1);
    }

    mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_IP);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
        perror("setsockopt");
        exit(1);
    }

    while (1) {
        int nbytes = recvfrom(sock, buffer, sizeof(buffer), 0, NULL, 0);
        if (nbytes < 0) {
            perror("recvfrom");
            exit(1);
        }
        buffer[nbytes] = '\0';
        printf("Received multicast/broadcast message: %s\n", buffer);
    }
}

int main() {
    receive_multicast();
    return 0;
}
