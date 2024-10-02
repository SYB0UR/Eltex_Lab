#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define QUEUE_NAME_SERVER_TO_CLIENT  "/server_to_client_queue"
#define QUEUE_NAME_CLIENT_TO_SERVER  "/client_to_server_queue"
#define MAX_SIZE    1024

int main() {
    mqd_t mq_server_to_client, mq_client_to_server;
    char buffer[MAX_SIZE];

    mq_server_to_client = mq_open(QUEUE_NAME_SERVER_TO_CLIENT, O_RDWR);
    if (mq_server_to_client == (mqd_t)-1) {
        perror("mq_open server to client");
        exit(1);
    }

    mq_client_to_server = mq_open(QUEUE_NAME_CLIENT_TO_SERVER, O_RDWR);
    if (mq_client_to_server == (mqd_t)-1) {
        perror("mq_open client to server");
        exit(1);
    }

    if (mq_receive(mq_server_to_client, buffer, MAX_SIZE, NULL) == -1) {
        perror("mq_receive");
        exit(1);
    }

    printf("Received: %s\n", buffer);

    strcpy(buffer, "Hello!");
    if (mq_send(mq_client_to_server, buffer, MAX_SIZE, 0) == -1) {
        perror("mq_send");
        exit(1);
    }

    printf("Sent: %s\n", buffer);

    if (mq_close(mq_server_to_client) == -1) {
        perror("mq_close server to client");
        exit(1);
    }

    if (mq_close(mq_client_to_server) == -1) {
        perror("mq_close client to server");
        exit(1);
    }

    return 0;
}
