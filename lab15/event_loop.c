#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() {
    sigset_t set;
    int sig;

    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);

    if (sigprocmask(SIG_BLOCK, &set, NULL) == -1) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }

    printf("Ожидание сигнала SIGUSR1...\n");

    while (1) {
        if (sigwait(&set, &sig) == 0) {
            if (sig == SIGUSR1) {
                printf("Получен сигнал SIGUSR1\n");
            }
        } else {
            perror("sigwait");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
