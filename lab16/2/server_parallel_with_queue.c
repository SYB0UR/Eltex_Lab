 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>

#define PORT 8080
#define QUEUE_SIZE 5

int server_fd;
int client_queue[QUEUE_SIZE];
int queue_front = 0;
int queue_rear = -1;
int queue_count = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void handle_sigint(int sig) {
    printf("Terminating server...\n");
    close(server_fd);
    exit(0);
}

void enqueue(int client_socket) {
    pthread_mutex_lock(&lock);
    if (queue_count < QUEUE_SIZE) {
        queue_rear = (queue_rear + 1) % QUEUE_SIZE;
        client_queue[queue_rear] = client_socket;
        queue_count++;
    }
    pthread_mutex_unlock(&lock);
}

int dequeue() {
    pthread_mutex_lock(&lock);
    int client_socket = -1;
    if (queue_count > 0) {
        client_socket = client_queue[queue_front];
        queue_front = (queue_front + 1) % QUEUE_SIZE;
        queue_count--;
    }
    pthread_mutex_unlock(&lock);
    return client_socket;
}

void *handle_client(void *arg) {
    int client_socket = *((int *)arg);
    free(arg);
    char buffer[1024] = {0};
    int bytes_read;
    while ((bytes_read = read(client_socket, buffer, 1024)) > 0) {
        buffer[bytes_read] = '\0';
        printf("Client: %s\n", buffer);
        send(client_socket, "Hello from server", 18, 0);
    }
    close(client_socket);
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

    while (1) {
        int client_socket;
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        enqueue(client_socket);

        pthread_t thread_id;
        int *pclient = malloc(sizeof(int));
        *pclient = dequeue();
        pthread_create(&thread_id, NULL, handle_client, pclient);
        pthread_detach(thread_id);
    }

    close(server_fd);
    return 0;
}
