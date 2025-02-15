TARGET = file_manager
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
LIBS = -lncurses
SRCS = lab9_2.c Funclab9_2.c RBTree.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
		$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
		$(CC) $(CFLAGS) -o $@ -c $<

clean:
		rm -f $(OBJS) $(TARGET)

.PHONY: all clean
