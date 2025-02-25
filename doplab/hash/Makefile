TARGET = main
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRCS = main.c hash_table.c
OBJS = main.o hash_table.o

$(TARGET): $(OBJS)
        $(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c hash_table.h
        $(CC) $(CFLAGS) -c main.c -o main.o

hash_table.o: hash_table.c hash_table.h
        $(CC) $(CFLAGS) -c hash_table.c -o hash_table.o

clean:
        rm -f $(TARGET) $(OBJS)