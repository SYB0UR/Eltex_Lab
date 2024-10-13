#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>

#define PORT 8080
#define THREAD_POOL_SIZE 4

int server_fd;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int client_queue[THREAD_POOL_SIZE];
int queue_size = 0;

void handle_sigint(int sig) {
    printf("Terminating server...\n");
    close(server_fd);
    exit(0);
}

void *handle_client(void *arg) {
    while (1) {
        int client_socket;

        pthread_mutex_lock(&lock);
        while (queue_size == 0) {
            pthread_cond_wait(&cond, &lock);
        }
        client_socket = client_queue[--queue_size];
        pthread_mutex_unlock(&lock);

        char buffer[1024] = {0};
        int bytes_read;
        while ((bytes_read = read(client_socket, buffer, 1024)) > 0) {
            buffer[bytes_read] = '\0';
            printf("Client: %s\n", buffer);
            send(client_socket, "Hello from server", 18, 0);
        }
        close(client_socket);
    }
    return NULL;
}

int main() {
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    signal(SIGINT, handle_sigint);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    pthread_t thread_pool[THREAD_POOL_SIZE];
    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_create(&thread_pool[i], NULL, handle_client, NULL);
    }

    while (1) {
        int client_socket;
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        pthread_mutex_lock(&lock);
        client_queue[queue_size++] = client_socket;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
    }

    close(server_fd);
    return 0;
}
