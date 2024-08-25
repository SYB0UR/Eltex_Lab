#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
    pid_t pid1 = fork();
    if (pid1 == 0) {
        
        printf("Process 1: PID = %d, PPID = %d\n", getpid(), getppid());
        pid_t pid3 = fork();
        if (pid3 == 0) {
            printf("Process 3: PID = %d, PPID = %d\n", getpid(), getppid());
            exit(0);
        } else if (pid3 > 0) {
            pid_t pid4 = fork();
            if (pid4 == 0) {
                printf("Process 4: PID = %d, PPID = %d\n", getpid(), getppid());
                exit(0);
            } else if (pid4 > 0) {
                int status;
                waitpid(pid3, &status, 0);
                printf("Process 3 exited with status %d\n", WEXITSTATUS(status));
                waitpid(pid4, &status, 0);
                printf("Process 4 exited with status %d\n", WEXITSTATUS(status));
            }
        }
        exit(0);
    } else if (pid1 > 0) {
        pid_t pid2 = fork();
        if (pid2 == 0) {
            printf("Process 2: PID = %d, PPID = %d\n", getpid(), getppid());
            pid_t pid5 = fork();
            if (pid5 == 0) {
                printf("Process 5: PID = %d, PPID = %d\n", getpid(), getppid());
                exit(0);
            } else if (pid5 > 0) {
                int status;
                waitpid(pid5, &status, 0);
                printf("Process 5 exited with status %d\n", WEXITSTATUS(status));
            }
            exit(0);
        } else if (pid2 > 0) {
            int status;
            waitpid(pid1, &status, 0);
            printf("Process 1 exited with status %d\n", WEXITSTATUS(status));
            waitpid(pid2, &status, 0);
            printf("Process 2 exited with status %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}
