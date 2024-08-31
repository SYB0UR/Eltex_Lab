CC = gcc
CFLAGS = -Wall -Werror -c -pthread

SRC1 = lab11_1.c lab11_1_Func.c
SRC2 = lab11_2.c lab11_2_Func.c
SRC3 = lab11_3.c lab11_3_Func.c

OBJ1 = lab11_1.o lab11_1_Func.o
OBJ2 = lab11_2.o lab11_2_Func.o
OBJ3 = lab11_3.o lab11_3_Func.o

EXEC1 = lab11_1
EXEC2 = lab11_2
EXEC3 = lab11_3

all: $(EXEC1) $(EXEC2) $(EXEC3)
		rm *.o

$(EXEC1): $(OBJ1)
		$(CC) $(OBJ1) -o $(EXEC1)
$(EXEC2): $(OBJ2)
		$(CC) $(OBJ2) -o $(EXEC2)
$(EXEC3): $(OBJ3)
		$(CC) $(OBJ3) -o $(EXEC3)

%.o: %.c
		$(CC) $(CFLAGS) $< -o $@

clean:
		rm -f $(OBJ1) $(OBJ2) $(OBJ3) $(EXEC1) $(EXEC2) $(EXEC3)

