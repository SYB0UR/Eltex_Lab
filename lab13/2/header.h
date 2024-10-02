#ifndef HEADER_H
#define HEADER_H

void sigint_handler(int signum);

struct msgbuf
{
    long mtype;
    char mname[32];
    char mtext[256];
};

void connection_to_server(void);
struct msgbuf get_message(void);
void send_message(char message[256]);

void win_user_f(void);
void* win_chat_f(void *arg);
void* win_input_f(void *arg);
void initialize_ui(void);

#endif 
