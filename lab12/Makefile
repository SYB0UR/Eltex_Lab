CC = gcc
CFLAGS = -Wall -Werror -c

SRC1 = lab12_1.c 
SRC2 = lab12_2_client.c
SRC3 = lab12_2_server.c
SRC4 = lab12_3.c lab12_3_Func.c

OBJ1 = lab12_1.o 
OBJ2 = lab12_2_client.o
OBJ3 = lab12_2_server.o
OBJ4 = lab12_3.o lab12_3_Func.o

EXEC1 = lab12_1
EXEC2 = lab12_2_client
EXEC3 = lab12_2_server
EXEC4 = lab12_3

all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4)
		rm *.o

$(EXEC1): $(OBJ1)
		$(CC) $(OBJ1) -o $(EXEC1)
$(EXEC2): $(OBJ2)
		$(CC) $(OBJ2) -o $(EXEC2)
$(EXEC3): $(OBJ3)
		$(CC) $(OBJ3) -o $(EXEC3)
$(EXEC4): $(OBJ4)
		$(CC) $(OBJ4) -o $(EXEC4)
%.o: %.c
		$(CC) $(CFLAGS) $< -o $@

clean:
		rm -f $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4)

