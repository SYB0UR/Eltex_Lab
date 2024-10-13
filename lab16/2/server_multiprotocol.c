#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <string.h>

#define TCP_PORT 8080
#define UDP_PORT 8081
#define THREAD_POOL_SIZE 4

int tcp_socket, udp_socket;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int client_queue[1024];
int queue_size = 0;

void *handle_tcp_client(void *arg) {
    while (1) {
        int client_socket;
        pthread_mutex_lock(&lock);
        while (queue_size == 0) {
            pthread_cond_wait(&cond, &lock);
        }
        client_socket = client_queue[--queue_size];
        pthread_mutex_unlock(&lock);

        char buffer[1024];
        int bytes_read;
        while ((bytes_read = read(client_socket, buffer, sizeof(buffer))) > 0) {
            buffer[bytes_read] = '\0';
            printf("Received TCP: %s\n", buffer);
            send(client_socket, "Hello, TCP Client!", 18, 0);
        }
        close(client_socket);
    }
    return NULL;
}

void *handle_udp_client(void *arg) {
    int udp_socket = *(int *)arg;
    char buffer[1024];
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);

    while (1) {
        int bytes_read = recvfrom(udp_socket, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &addr_len);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            printf("Received UDP: %s\n", buffer);
            sendto(udp_socket, "Hello, UDP Client!", 18, 0, (struct sockaddr*)&client_addr, addr_len);
        }
    }
    return NULL;
}

int main() {
    struct sockaddr_in tcp_addr, udp_addr;
    int opt = 1;

    if ((tcp_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("TCP socket failed");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(tcp_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt TCP");
        exit(EXIT_FAILURE);
    }
    tcp_addr.sin_family = AF_INET;
    tcp_addr.sin_addr.s_addr = INADDR_ANY;
    tcp_addr.sin_port = htons(TCP_PORT);
    if (bind(tcp_socket, (struct sockaddr *)&tcp_addr, sizeof(tcp_addr)) < 0) {
        perror("TCP bind failed");
        close(tcp_socket);
        exit(EXIT_FAILURE);
    }
    if (listen(tcp_socket, 3) < 0) {
        perror("TCP listen failed");
        close(tcp_socket);
        exit(EXIT_FAILURE);
    }

    if ((udp_socket = socket(AF_INET, SOCK_DGRAM, 0)) == 0) {
        perror("UDP socket failed");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(udp_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt UDP");
        exit(EXIT_FAILURE);
    }
    udp_addr.sin_family = AF_INET;
    udp_addr.sin_addr.s_addr = INADDR_ANY;
    udp_addr.sin_port = htons(UDP_PORT);
    if (bind(udp_socket, (struct sockaddr *)&udp_addr, sizeof(udp_addr)) < 0) {
        perror("UDP bind failed");
        close(udp_socket);
        exit(EXIT_FAILURE);
    }

    pthread_t thread_pool[THREAD_POOL_SIZE];
    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_create(&thread_pool[i], NULL, handle_tcp_client, NULL);
    }

    pthread_t udp_thread;
    pthread_create(&udp_thread, NULL, handle_udp_client, &udp_socket);

    fd_set readfds;
    while (1) {
        FD_ZERO(&readfds);
        FD_SET(tcp_socket, &readfds);
        FD_SET(udp_socket, &readfds);
        int max_sd = tcp_socket > udp_socket ? tcp_socket : udp_socket;

        int activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        if (activity < 0) {
            perror("select error");
            exit(EXIT_FAILURE);
        }


        if (FD_ISSET(tcp_socket, &readfds)) {
            int client_socket;
            struct sockaddr_in address;
            socklen_t addrlen = sizeof(address);
            if ((client_socket = accept(tcp_socket, (struct sockaddr *)&address, &addrlen)) < 0) {
                perror("accept failed");
                close(tcp_socket);
                exit(EXIT_FAILURE);
            }

            pthread_mutex_lock(&lock);
            client_queue[queue_size++] = client_socket;
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&lock);
        }
    }

    close(tcp_socket);
    close(udp_socket);
    return 0;
}
