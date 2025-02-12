CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = main
SRCS = main.c abonent.c
OBJS = $(SRCS:.c=.o)
DEPS = abonent.h

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
        $(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c $(DEPS)
        $(CC) $(CFLAGS) -c $< -o $@

clean:
        rm -f $(OBJS) $(TARGET)