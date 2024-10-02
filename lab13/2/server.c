#include <signal.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/msg.h>

#define MSG_SIZE 256
#define MAX_USERS 5
#define QUEUE_KEY 1234

volatile sig_atomic_t paused = 1;
volatile int global_flag = 1;
char list_users[MAX_USERS][32];
pthread_t wait_new_users_id;
pthread_t common_channel_logic_id;

pthread_mutex_t global_mutex;

struct msgbuf
{
    long mtype;
    char mname[32];
    char mtext[MSG_SIZE];
};

/**
 * Обработчик сигнала SIGINT (Ctrl+C).
 * @param signum Номер сигнала.
 *
 * Завершает работу потоков и устанавливает флаг паузы в 0.
 */
void sigint_handler(int signum)
{
    global_flag = 0;
    pthread_cancel(wait_new_users_id);
    pthread_cancel(common_channel_logic_id);
    paused = 0;
}

/**
 * Инициализация действий.
 * @param msgid Указатель на идентификатор очереди сообщений.
 *
 * Создает очередь сообщений и инициализирует список пользователей.
 */
void init_actions(int *msgid)
{
    *msgid = msgget(QUEUE_KEY, 0644 | IPC_CREAT);
    if (*msgid == -1)
    {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_USERS; i++)
    {
        strcpy(list_users[i], "");
    }
}

/**
 * Ожидание новых пользователей.
 * @param arg Указатель на идентификатор очереди сообщений.
 * @return NULL
 *
 * Ожидает новых пользователей и добавляет их в список.
 */
void* wait_new_users(void *arg)
{
    int i;
    int msgid = *(int *)arg;
    struct msgbuf buffer;

    while (global_flag)
    {
        if (msgrcv(msgid, (void *)&buffer, sizeof(struct msgbuf), 2, 0) == -1)
        {
            perror("msgrcv");
        }

        for (i = 0; i < MAX_USERS; i++)
        {
            if (strcmp(list_users[i], "") == 0)
            {
                strcpy(list_users[i], buffer.mname);
                snprintf(buffer.mtext, sizeof(buffer.mtext), "%d", i + 4);
                strcpy(buffer.mname, "server");
                buffer.mtype = 1;
                break;
            }
        }
        msgsnd(msgid, (void *)&buffer, sizeof(struct msgbuf), 0);
        printf("%s: %s\n", buffer.mname, buffer.mtext);

        buffer.mtype = 3;
        strcpy(buffer.mname, "new_user");
        snprintf(buffer.mtext, sizeof(buffer.mtext), "user %s joined the chat", list_users[i]);
        msgsnd(msgid, (void *)&buffer, sizeof(struct msgbuf), 0);
    }

    return NULL;
}

/**
 * Логика общего канала.
 * @param arg Указатель на идентификатор очереди сообщений.
 * @return NULL
 *
 * Обрабатывает сообщения общего канала и отправляет их всем пользователям.
 */
void* common_channel_logic(void *arg)
{
    int msgid = *(int *)arg;
    struct msgbuf buffer;

    while(global_flag)
    {
        if (msgrcv(msgid, (void *)&buffer, sizeof(struct msgbuf), 3, 0) == -1)
        {
            perror("msgrcv");
        }
        printf("rcv ch%ld: %s: %s\n", buffer.mtype, buffer.mname, buffer.mtext);

        for (int i = 0; i < MAX_USERS; i++)
        {
            buffer.mtype = i + 4;
            if (msgsnd(msgid, (void *)&buffer, sizeof(struct msgbuf), IPC_NOWAIT) == -1)
            {
                perror("msgsnd");
            }
            printf("snd ch%ld: %s: %s\n", buffer.mtype, buffer.mname, buffer.mtext);
        }
    }

    return NULL;
}

/**
 * Главная функция.
 *
 * Инициализирует переменные, создает потоки и ожидает завершения.
 */
int main()
{
    signal(SIGINT, sigint_handler);

    int msgid;
    init_actions(&msgid);

    if (pthread_create(&wait_new_users_id, NULL, wait_new_users, (void *)&msgid) != 0)
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&common_channel_logic_id, NULL, common_channel_logic, (void *)&msgid) != 0)
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    while (paused == 1)
    {
        pause();
    }

    msgctl(msgid, IPC_RMID, NULL);

    exit(EXIT_SUCCESS);
}
