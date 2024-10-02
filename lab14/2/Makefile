CC = gcc
CFLAGS = -Wall -Wextra -c -pthread
LDFLAGS = -lncurses

SRC_SERVER = server.c
SRC_CLIENT = main.c initialize_ui.c

OBJ_SERVER = server.o
OBJ_CLIENT = main.o initialize_ui.o

EXEC_SERVER = server
EXEC_CLIENT = client

all: $(EXEC_SERVER) $(EXEC_CLIENT)
		rm *.o

$(EXEC_SERVER): $(OBJ_SERVER)
		$(CC) $(OBJ_SERVER) -o $(EXEC_SERVER)

$(EXEC_CLIENT): $(OBJ_CLIENT)
		$(CC) $(OBJ_CLIENT) -o $(EXEC_CLIENT) $(LDFLAGS)

%.o: %.c
		$(CC) $(CFLAGS) $< -o $@

clean:
		rm -f $(OBJ_SERVER) $(OBJ_CLIENT) $(EXEC_SERVER) $(EXEC_CLIENT)
