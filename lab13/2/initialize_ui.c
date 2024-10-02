#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ncurses.h>
#include <stdlib.h>
#include <sys/msg.h>

#include "header.h"
extern volatile int running;
#define MSG_SIZE 256
extern int msgid;
extern long num_listen_chanel;
extern char list_of_users[20][32];
extern int num_users;
extern char name[32];

WINDOW* win_user;
pthread_mutex_t ncurses_mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * Обновление окна пользователей.
 *
 * Обновляет список пользователей в окне и отображает его.
 */
void win_user_f(void)
{
    pthread_mutex_lock(&ncurses_mutex);

    werase(win_user);

    for (int i = 0; i < num_users; i++)
    {
        mvwprintw(win_user, i + 1, 1, "%s", list_of_users[i]);
    }

    box(win_user, 0, 0);
    mvwprintw(win_user, 0, 1, "users");
    wrefresh(win_user);

    pthread_mutex_unlock(&ncurses_mutex);
}

/**
 * Функция потока для окна чата.
 * @param arg Указатель на окно чата.
 * @return NULL
 *
 * Обрабатывает и отображает сообщения в окне чата.
 */
void* win_chat_f(void *arg)
{
    WINDOW* win_chat = (WINDOW *)arg;

    int y, x;
    getmaxyx(win_chat, y, x);

    struct msgbuf buffer;
    static int message_id = 0; 

    while (1)
    {
        buffer = get_message();
        pthread_mutex_lock(&ncurses_mutex);

        for (int iy = 1; iy < y - 1; iy++)
        {
            char line_buffer[x + 1];

            mvwinnstr(win_chat, iy, 0, line_buffer, x);

            mvwaddstr(win_chat, iy - 1, 0, line_buffer);
        }

        for (int ix = 0; ix < x; ix++) {
            mvwaddch(win_chat, y - 2, ix, ' ');
        }

        if (strcmp(buffer.mname, "server") == 0)
        {
            mvwprintw(win_chat, y - 2, 1, "%s(%d): %s", buffer.mname, message_id, buffer.mtext);
        } else
        {
            mvwprintw(win_chat, y - 2, 1, "%s(%d): %s", buffer.mname, message_id, buffer.mtext);
        }

        message_id++;

        box(win_chat, 0, 0);
        wrefresh(win_chat);

        pthread_mutex_unlock(&ncurses_mutex);
    }
    return NULL;
}

/**
 * Функция потока для окна ввода.
 * @param arg Указатель на окно ввода.
 * @return NULL
 *
 * Обрабатывает ввод пользователя и отправляет сообщения.
 */
void* win_input_f(void *arg)
{
    WINDOW* win_input = (WINDOW *)arg;

    char input_mtext[MSG_SIZE];
    char copy_mtext[MSG_SIZE];

    while (1)
    {
        pthread_mutex_lock(&ncurses_mutex);

        werase(win_input);
        box(win_input, 0, 0);

        mvwprintw(win_input, 1, 1, "->");
        wrefresh(win_input);

        pthread_mutex_unlock(&ncurses_mutex);

        echo();
        wgetstr(win_input, input_mtext);
        noecho();

        if (strcmp(input_mtext, "#exit") == 0)
        {
            struct msgbuf buffer;
            buffer.mtype = 4; 
            strcpy(buffer.mname, name);
            snprintf(buffer.mtext, MSG_SIZE, "exit:%s", name);

            if (msgsnd(msgid, (void *)&buffer, sizeof(struct msgbuf), 0) == -1)
            {
                perror("msgsnd");
            }
            pthread_mutex_lock(&ncurses_mutex);
            werase(win_input);
            box(win_input, 0, 0);
            mvwprintw(win_input, 1, 1, "User %s has exited.", name);
            wrefresh(win_input);
            pthread_mutex_unlock(&ncurses_mutex);

            refresh();
            endwin();

            exit(EXIT_SUCCESS);
        }
        strcpy(copy_mtext, input_mtext);
        send_message(copy_mtext);
    }
    return NULL;
}

/**
 * Инициализация пользовательского интерфейса.
 *
 * Настраивает окна для чата, ввода и списка пользователей.
 */
void initialize_ui(void)
{
    initscr();
    cbreak();
    noecho();
    start_color();

    pthread_t win_chat_id, win_input_id;

    int maxY, maxX;

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);

    attron(COLOR_PAIR(1));

    getmaxyx(stdscr, maxY, maxX);

    if (maxY < 30 || maxX < 53)
    {
        endwin();
        printf("error: screen too small. minimum size (53;30). ur (%d;%d)", maxY, maxX);
        kill(getpid(), SIGINT);
    }


    WINDOW *win_chat = newwin(maxY - 4, maxX * 0.75, 0, 0);
    WINDOW *win_input = newwin(4, maxX, maxY - 4, 0);
    win_user = newwin(maxY - 4, maxX * 0.25 + 1, 0, maxX * 0.75);

    werase(stdscr);
    refresh();

    if (pthread_create(&win_chat_id, NULL, win_chat_f, (void *)win_chat) != 0)
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&win_input_id, NULL, win_input_f, (void *)win_input) != 0)
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
}
