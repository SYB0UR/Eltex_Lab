#include <signal.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_KEY 1234
#define MSG_SIZE 256
#define MAX_USERS 5

volatile sig_atomic_t paused = 1;
volatile int global_flag = 1;
char list_users[MAX_USERS][32];
pthread_t wait_new_users_id;
pthread_t common_channel_logic_id;

pthread_mutex_t global_mutex;

struct msgbuf {
    char mname[32];
    char mtext[MSG_SIZE];
};

struct shared_memory {
    struct msgbuf messages[100];
    int message_count;
    char users[MAX_USERS][32];
    int user_count;
};

/**
 * Обработчик сигнала SIGINT (Ctrl+C).
 *
 * Завершает работу потоков и устанавливает флаг паузы в 0.
 */
void sigint_handler() {
    global_flag = 0;
    pthread_cancel(wait_new_users_id);
    pthread_cancel(common_channel_logic_id);
    paused = 0;
}

/**
 * Инициализация действий.
 * @param shmid Указатель на идентификатор разделяемой памяти.
 * @param shm Указатель на указатель на структуру разделяемой памяти.
 *
 * Создает разделяемую память и инициализирует структуру разделяемой памяти.
 */
void init_actions(int *shmid, struct shared_memory **shm) {
    *shmid = shmget(SHM_KEY, sizeof(struct shared_memory), 0644 | IPC_CREAT);
    if (*shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    *shm = shmat(*shmid, NULL, 0);
    if (*shm == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    (*shm)->message_count = 0;
    (*shm)->user_count = 0;
}

/**
 * Ожидание новых пользователей.
 * @param arg Указатель на структуру разделяемой памяти.
 * @return NULL
 *
 * Ожидает новых пользователей и добавляет их в список.
 */
void* wait_new_users(void *arg) {
    struct shared_memory *shm = (struct shared_memory *)arg;

    while (global_flag) {
        if (shm->user_count < MAX_USERS){
        }
        usleep(500000);
    }

    return NULL;
}

/**
 * Логика общего канала.
 * @return NULL
 *
 * Обрабатывает сообщения и уведомляет всех пользователей.
 */
void* common_channel_logic() {


    while(global_flag) {
        usleep(500000);
    }

    return NULL;
}

/**
 * Главная функция.
 *
 * Инициализирует переменные, создает потоки и ожидает завершения.
 */
int main() {
    signal(SIGINT, sigint_handler);

    int shmid;
    struct shared_memory *shm;
    init_actions(&shmid, &shm);

    if (pthread_create(&wait_new_users_id, NULL, wait_new_users, (void *)shm) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&common_channel_logic_id, NULL, common_channel_logic, (void *)shm) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    while (paused == 1) {
        pause();
    }

    shmctl(shmid, IPC_RMID, NULL);

    exit(EXIT_SUCCESS);
}
