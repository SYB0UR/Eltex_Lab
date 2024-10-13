#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345

void receive_broadcast() {
    int sock;
    struct sockaddr_in addr;
    char buffer[1024];

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }

    int broadcast = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0) {
        perror("setsockopt");
        exit(1);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_BROADCAST); 
    addr.sin_port = htons(PORT);

    if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(1);
    }

    while (1) {
        int nbytes = recvfrom(sock, buffer, sizeof(buffer), 0, NULL, 0);
        if (nbytes < 0) {
            perror("recvfrom");
            exit(1);
        }
        buffer[nbytes] = '\0';
        printf("Received broadcast message: %s\n", buffer);
    }
}

int main() {
    receive_broadcast();
    return 0;
}
