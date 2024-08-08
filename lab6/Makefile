TARGET = main
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRCS = main.c
FUNC = func.c
OBJS1 = $(SRCS:.c=.o)
OBJS2 = $(FUNC:.c=.o)


all: $(TARGET)

$(TARGET): $(OBJS1) $(OBJS2)
		$(CC) $(CFLAGS) -o $(TARGET) $(OBJS1) $(OBJS2)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJS1)$(OBJS2) $(TARGET)

rebuild: clean all
