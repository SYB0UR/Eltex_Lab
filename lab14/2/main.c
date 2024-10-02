#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <ncurses.h>

#include "header.h"

#define SHM_KEY 1234
#define MSG_SIZE 256

char name[32];
volatile sig_atomic_t paused = 1;
int shmid;
struct shared_memory *shm;

/**
 * Обработчик сигнала SIGINT (Ctrl+C).
 *
 * Завершает работу программы при получении сигнала.
 */
void sigint_handler(int) {
    paused = 0;
    endwin();
    exit(EXIT_SUCCESS);
}

/**
 * Подключение к серверу.
 *
 * Устанавливает соединение с сервером и добавляет пользователя в список.
 */
void connection_to_server() {
    shmid = shmget(SHM_KEY, 0, 0);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    shm = shmat(shmid, NULL, 0);
    if (shm == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    printf("to exit enter the command #exit\n");
    printf("enter name: ");
    scanf("%s", name);


    strcpy(shm->users[shm->user_count], name);
    shm->user_count++;


    struct msgbuf buffer;
    strcpy(buffer.mname, "server");
    snprintf(buffer.mtext, MSG_SIZE, "user %s joined the chat", name);
    strcpy(shm->messages[shm->message_count].mname, buffer.mname);
    strcpy(shm->messages[shm->message_count].mtext, buffer.mtext);
    shm->message_count++;


    win_user_f();
}

/**
 * Получение сообщений.
 * @param arg Не используется.
 * @return NULL
 *
 * Получает сообщения из разделяемой памяти и отображает их в окне чата.
 */
void* receive_messages(void*) {


    while (1) {

    }

    return NULL;
}

/**
 * Отправка сообщения.
 * @param message Текст сообщения.
 *
 * Отправляет сообщение в разделяемую память.
 */
void send_message(char message[MSG_SIZE]) {
    struct msgbuf buffer;
    strcpy(buffer.mname, name);
    snprintf(buffer.mtext, MSG_SIZE, "%s", message);

    strcpy(shm->messages[shm->message_count].mname, buffer.mname);
    strcpy(shm->messages[shm->message_count].mtext, buffer.mtext);
    shm->message_count++;
}

/**
 * Мониторинг пользователей.
 * @param arg Не используется.
 * @return NULL
 *
 * Проверяет изменения в списке пользователей и обновляет окно пользователей.
 */
void* monitor_users(void* ) {
    int previous_user_count = shm->user_count;

    while (1) {
        if (shm->user_count != previous_user_count) {
            win_user_f();
            previous_user_count = shm->user_count;
        }
        usleep(500000); 
    }

    return NULL;
}

/**
 * Главная функция.
 *
 * Инициализирует соединение с сервером, пользовательский интерфейс и потоки.
 */
int main(void) {
    signal(SIGINT, sigint_handler);

    connection_to_server();
    initialize_ui();

    pthread_t monitor_users_id;
    if (pthread_create(&monitor_users_id, NULL, monitor_users, NULL) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    while (paused) {
        pause();
    }

    exit(EXIT_SUCCESS);
}
