CC = gcc
CFLAGS =
CLIENT_SRC = client.c
SERVER_SRC = server.c
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
