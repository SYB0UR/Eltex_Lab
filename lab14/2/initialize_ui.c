#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ncurses.h>
#include <stdlib.h>
#include <sys/shm.h>

#include "header.h"
extern volatile int running;
#define MSG_SIZE 256
extern struct shared_memory *shm;
extern char name[32];

WINDOW* win_user;
pthread_mutex_t ncurses_mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * Обновление окна пользователей.
 *
 * Обновляет список пользователей в окне и отображает его.
 */
void win_user_f(void) {
    pthread_mutex_lock(&ncurses_mutex);

    werase(win_user);

    for (int i = 0; i < shm->user_count; i++) {
        mvwprintw(win_user, i + 1, 1, "%s", shm->users[i]);
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
void* win_chat_f(void *arg) {
    WINDOW* win_chat = (WINDOW *)arg;

    int y, x;
    getmaxyx(win_chat, y, x);

    scrollok(win_chat, TRUE); 

    while (1) {
        pthread_mutex_lock(&ncurses_mutex);

        werase(win_chat);
        int start_line = (shm->message_count > y - 2) ? shm->message_count - (y - 2) : 0;
        for (int i = start_line; i < shm->message_count; i++) {
            mvwprintw(win_chat, i - start_line + 1, 1, "%s(%d): %s", shm->messages[i].mname, i + 1, shm->messages[i].mtext);
        }

        box(win_chat, 0, 0);
        wrefresh(win_chat);

        pthread_mutex_unlock(&ncurses_mutex);
        usleep(500000); 
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
void* win_input_f(void *arg) {
    WINDOW* win_input = (WINDOW *)arg;

    char input_mtext[MSG_SIZE];

    while (1) {
        pthread_mutex_lock(&ncurses_mutex);

        werase(win_input);
        box(win_input, 0, 0);

        mvwprintw(win_input, 1, 1, "->");
        wrefresh(win_input);

        pthread_mutex_unlock(&ncurses_mutex);

        echo();
        wgetstr(win_input, input_mtext);
        noecho();

        if (strcmp(input_mtext, "#exit") == 0) {
            struct msgbuf buffer;
            strcpy(buffer.mname, name);
            snprintf(buffer.mtext, MSG_SIZE, "exit:%s", name);

            strcpy(shm->messages[shm->message_count].mname, buffer.mname);
            strcpy(shm->messages[shm->message_count].mtext, buffer.mtext);
            shm->message_count++;

            for (int i = 0; i < shm->user_count; i++) {
                if (strcmp(shm->users[i], name) == 0) {
                    for (int j = i; j < shm->user_count - 1; j++) {
                        strcpy(shm->users[j], shm->users[j + 1]);
                    }
                    shm->user_count--;
                    break;
                }
            }
            win_user_f();
            refresh();
            endwin(); 

            exit(EXIT_SUCCESS);
        }
        send_message(input_mtext);
    }
    return NULL;
}

/**
 * Инициализация пользовательского интерфейса.
 *
 * Настраивает окна для чата, ввода и списка пользователей.
 */
void initialize_ui(void) {
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

    if (maxY < 30 || maxX < 53) {
        endwin();
        printf("error: screen too small. minimum size (53;30). ur (%d;%d)", maxY, maxX);
        kill(getpid(), SIGINT);
    }


    WINDOW *win_chat = newwin(maxY - 4, maxX * 0.75, 0, 0);
    WINDOW *win_input = newwin(4, maxX, maxY - 4, 0);
    win_user = newwin(maxY - 4, maxX * 0.25 + 1, 0, maxX * 0.75);

    werase(stdscr);
    refresh();

    if (pthread_create(&win_chat_id, NULL, win_chat_f, (void *)win_chat) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&win_input_id, NULL, win_input_f, (void *)win_input) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    win_user_f();
}

