#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/my_fifo"
#define BUF_SIZE 1024

int main() {
    int fd;
    char buf[BUF_SIZE];

    fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    ssize_t numRead = read(fd, buf, BUF_SIZE);
    if (numRead == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    write(STDOUT_FILENO, buf, numRead);
    close(fd);

    if (unlink(FIFO_NAME) == -1) {
        perror("unlink");
        exit(EXIT_FAILURE);
    }

    return 0;
}
