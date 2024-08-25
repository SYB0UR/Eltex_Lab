CC = gcc
CFLAGS = -Wall -Werror -c

SRC1 = lab10_1.c
SRC2 = lab10_2.c
SRC3 = lab10_3.c

OBJ1 = lab10_1.o
OBJ2 = lab10_2.o
OBJ3 = lab10_3.o

EXEC1 = lab10_1
EXEC2 = lab10_2
EXEC3 = lab10_3

all: $(EXEC1) $(EXEC2) $(EXEC3)
		rm *.o

$(EXEC1): $(OBJ1)
		$(CC) $(OBJ1) -o $(EXEC1)
$(EXEC2): $(OBJ2)
		$(CC) $(OBJ2) -o $(EXEC2)
$(EXEC3): $(OBJ3)
		$(CC) $(OBJ3) -o $(EXEC3)

%.o: %.c
		$(CC) $< -o $@ $(CFLAGS)

clean:
		rm -f $(OBJ1) $(OBJ2) $(OBJ3) $(EXEC1) $(EXEC2) $(EXEC3)

