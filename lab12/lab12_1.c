#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUF_SIZE 1024

int main() {
    int pipefd[2];
    pid_t cpid;
    char buf[BUF_SIZE];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {    
        close(pipefd[1]);          
        ssize_t numRead;
        while ((numRead = read(pipefd[0], buf, BUF_SIZE)) > 0) {
            write(STDOUT_FILENO, buf, numRead);
        }
        close(pipefd[0]);
        _exit(EXIT_SUCCESS);

    } else {            
        close(pipefd[0]);          
        write(pipefd[1], "Hi!", 3);
        close(pipefd[1]);          
        wait(NULL);                
        exit(EXIT_SUCCESS);
    }
}
