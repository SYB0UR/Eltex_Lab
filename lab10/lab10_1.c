#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        printf("Child process: PID = %d, PPID = %d\n", getpid(), getppid());
        exit(0);
    } else {
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);
        int status;
        waitpid(pid, &status, 0);
        printf("Child process exited with status %d\n", WEXITSTATUS(status));
    }

    return 0;
}
