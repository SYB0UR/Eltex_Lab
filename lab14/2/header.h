#ifndef HEADER_H
#define HEADER_H

void sigint_handler(int signum);

struct msgbuf {
    char mname[32];
    char mtext[256];
};

struct shared_memory {
    struct msgbuf messages[100];
    int message_count;
    char users[5][32];
    int user_count;
};

void connection_to_server(void);
void* receive_messages(void *arg);
void send_message(char message[256]);
void* monitor_users(void *arg);

void win_user_f(void);
void* win_chat_f(void *arg);
void* win_input_f(void *arg);
void initialize_ui(void);

#endif 
