#include "lab12_3.h" 


int main() {
    char input[MAX_INPUT];
    while (1) {
        printf("mybash> ");
        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            perror("fgets failed");
            continue;
        }
        input[strcspn(input, "\n")] = 0;
        if (strcmp(input, "exit") == 0) {
            break;
        }

        char *cmd1 = strtok(input, "|");
        char *cmd2 = strtok(NULL, "|");

        if (cmd2 == NULL) {
            pid_t pid = fork();
            if (pid < 0) {
                perror("fork failed");
                continue;
            } else if (pid == 0) {
                execute_command(cmd1);
            } else {
                int status;
                waitpid(pid, &status, 0);
                printf("Child process exited with status %d\n", WEXITSTATUS(status));
            }
        } else {
            int pipefd[2];
            if (pipe(pipefd) == -1) {
                perror("pipe failed");
                continue;
            }

            pid_t pid1 = fork();
            if (pid1 < 0) {
                perror("fork failed");
                continue;
            } else if (pid1 == 0) {
                close(pipefd[0]); 
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
                execute_command(cmd1);
            }

            pid_t pid2 = fork();
            if (pid2 < 0) {
                perror("fork failed");
                continue;
            } else if (pid2 == 0) {
                close(pipefd[1]); 
                dup2(pipefd[0], STDIN_FILENO);
                close(pipefd[0]);
                execute_command(cmd2);
            }
            close(pipefd[0]);
            close(pipefd[1]);
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);
        }
    }

    return 0;
}
