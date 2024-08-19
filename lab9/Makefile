CC = gcc
CFLAGS = -Wall -c
LDFLAGS = -lncurses
SRC2 = Funclab9_2.c lab9_2.c
SRC1 = lab9_1.c
OBJ1 = lab9_1.o
OBJ2 = Funclab9_2.o lab9_2.o
EXEC1 = lab9_1
EXEC2 = lab9_2

all: $(EXEC1) $(EXEC2)
		rm *.o
$(EXEC1): $(OBJ1)
		$(CC) $(OBJ1) -o $(EXEC1)

$(EXEC2): $(OBJ2)
		$(CC) $(OBJ2) -o $(EXEC2) $(LDFLAGS)

%.o: %.c
		$(CC) $(CFLAGS) $< -o $@

clean:
		rm -f $(OBJ1) $(OBJ2) $(EXEC1) $(EXEC2) output.txt

