CC = gcc
CFLAGS = -Wall -Wextra -pedantic

all: server client_broad client_multi

server: server.c
		$(CC) $(CFLAGS) -o server server.c

client_broad: client_broad.c
		$(CC) $(CFLAGS) -o client_broad client_broad.c

client_multi: client_multi.c
		$(CC) $(CFLAGS) -o client_multi client_multi.c

clean:
		rm -f server client_broad client_multi
