#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>
#include <ncurses.h>

#include "header.h"

#define QUEUE_KEY 1234
#define MSG_SIZE 256

char name[32];
long num_listen_chanel;
volatile sig_atomic_t paused = 1;
int msgid;
char list_of_users[20][32];
int num_users;

/**
 * Обработчик сигнала SIGINT (Ctrl+C).
 * @param signum Номер сигнала.
 *
 * Отправляет сообщение о выходе пользователя и завершает программу.
 */
void sigint_handler(int signum)
{
    struct msgbuf buffer;
    buffer.mtype = 4; 
    strcpy(buffer.mname, name);
    snprintf(buffer.mtext, MSG_SIZE, "exit:%s", name);

    if (msgsnd(msgid, (void *)&buffer, sizeof(struct msgbuf), 0) == -1)
    {
        perror("msgsnd");
    }
    paused = 0;
    endwin();
    exit(EXIT_SUCCESS);
}

/**
 * Подключение к серверу.
 *
 * Устанавливает соединение с сервером и получает канал для прослушивания.
 */
void connection_to_server()
{
    msgid = msgget(QUEUE_KEY, 0);
    if (msgid == -1)
    {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    struct msgbuf buffer;
    printf("to exit enter the command #exit\n");
    printf("enter name: ");
    scanf("%s", buffer.mname);

    strcpy(name, buffer.mname);
    buffer.mtype = 2;

    if (msgsnd(msgid, (void *)&buffer, sizeof(struct msgbuf), 0) == -1)
    {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    if (msgrcv(msgid, (void *)&buffer, sizeof(struct msgbuf), 1, 0) == -1)
    {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    num_listen_chanel = atoi(buffer.mtext);
    printf("%s: chanel to connect: %ld\n", buffer.mname, num_listen_chanel);
    return;
}

/**
 * Получение сообщения.
 * @return Структура сообщения.
 *
 * Получает сообщение из очереди и обрабатывает его.
 */
struct msgbuf get_message(void)
{
    struct msgbuf buffer;

    if (msgrcv(msgid, (void *)&buffer, sizeof(struct msgbuf), num_listen_chanel, 0) == -1)
    {
        perror("msgrcv");
        kill(getpid(), SIGINT);
    }

    if (strcmp(buffer.mname, "new_user") == 0)
    {
        char copy_mtext[MSG_SIZE];
        char token[32];
        strcpy(buffer.mname, "server");

        strcpy(copy_mtext, buffer.mtext);
        strcpy(token, strtok(copy_mtext, " "));
        strcpy(token, strtok(NULL, " "));

        strcpy(list_of_users[num_users], token);
        num_users += 1;
        win_user_f();
    }
    else if (strncmp(buffer.mtext, "exit:", 5) == 0)
    {
        char *exiting_user = buffer.mtext + 5;
        for (int i = 0; i < num_users; i++)
        {
            if (strcmp(list_of_users[i], exiting_user) == 0)
            {
                for (int j = i; j < num_users - 1; j++)
                {
                    strcpy(list_of_users[j], list_of_users[j + 1]);
                }
                num_users--;
                win_user_f();
                break;
            }
        }
    }

    return buffer;
}

/**
 * Отправка сообщения.
 * @param message Текст сообщения.
 *
 * Отправляет сообщение в очередь сообщений.
 */
void send_message(char message[MSG_SIZE])
{
    static int message_id = 0;
    struct msgbuf buffer;

    buffer.mtype = 3;
    strcpy(buffer.mname, name);
    snprintf(buffer.mtext, MSG_SIZE, "%s", message);

    if (strcmp(buffer.mtext, "\n") != 0)
    {
        if (msgsnd(msgid, (void *)&buffer, sizeof(struct msgbuf), 0))
        {
            perror("msgsnd");
            kill(getpid(), SIGINT);
        }
    }
}

/**
 * Главная функция.
 *
 * Инициализирует переменные, подключается к серверу и запускает интерфейс.
 */
int main(void)
{
    num_users = 0;
    signal(SIGINT, sigint_handler);

    connection_to_server();
    initialize_ui();

    while (paused)
    {
        pause();
    }

    exit(EXIT_SUCCESS);
}
