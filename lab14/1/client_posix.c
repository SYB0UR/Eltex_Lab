#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define SHARED_MEMORY_NAME "/posix_shm"
#define MAX_SIZE 1024

int main() {
    int shm_fd;
    char *shm_ptr;

    shm_fd = shm_open(SHARED_MEMORY_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    shm_ptr = mmap(0, MAX_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    printf("Received: %s\n", shm_ptr);

    strcpy(shm_ptr, "Hello!");
    printf("Sent: %s\n", shm_ptr);

    if (munmap(shm_ptr, MAX_SIZE) == -1) {
        perror("munmap");
        exit(1);
    }

    return 0;
}
