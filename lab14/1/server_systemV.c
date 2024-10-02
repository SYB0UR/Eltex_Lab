#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_KEY 1234
#define MAX_SIZE 1024

int main() {
    int shmid;
    char *shm_ptr;

    shmid = shmget(SHM_KEY, MAX_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    shm_ptr = shmat(shmid, NULL, 0);
    if (shm_ptr == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    strcpy(shm_ptr, "Hi!");
    printf("Sent: %s\n", shm_ptr);

    while (strcmp(shm_ptr, "Hello!") != 0) {
        sleep(1);
    }

    printf("Received: %s\n", shm_ptr);

    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        exit(1);
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }

    return 0;
}
