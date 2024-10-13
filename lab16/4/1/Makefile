CC = gcc
CFLAGS = -Wall
CLIENT_SRC = client_udp.c
SERVER_SRC = server_udp.c
CLIENT_BIN = client
SERVER_BIN = server

all: $(CLIENT_BIN) $(SERVER_BIN)

$(CLIENT_BIN): $(CLIENT_SRC)
		$(CC) $(CFLAGS) -o $(CLIENT_BIN) $(CLIENT_SRC)

$(SERVER_BIN): $(SERVER_SRC)
		$(CC) $(CFLAGS) -o $(SERVER_BIN) $(SERVER_SRC)

clean:
		rm -f $(CLIENT_BIN) $(SERVER_BIN)

.PHONY: all clean
