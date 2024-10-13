CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: client_loc_udp server_loc_udp server_inet_tcp client_inet_tcp server_loc_tcp client_loc_tcp server_inet_udp client_inet_udp

client_loc_udp: client_loc_udp.c
		$(CC) $(CFLAGS) -o client_loc_udp client_loc_udp.c

server_loc_udp: server_loc_udp.c
		$(CC) $(CFLAGS) -o server_loc_udp server_loc_udp.c

server_inet_tcp: server_inet_tcp.c
		$(CC) $(CFLAGS) -o server_inet_tcp server_inet_tcp.c

client_inet_tcp: client_inet_tcp.c
		$(CC) $(CFLAGS) -o client_inet_tcp client_inet_tcp.c

server_loc_tcp: server_loc_tcp.c
		$(CC) $(CFLAGS) -o server_loc_tcp server_loc_tcp.c

client_loc_tcp: client_loc_tcp.c
		$(CC) $(CFLAGS) -o client_loc_tcp client_loc_tcp.c

server_inet_udp: server_inet_udp.c
		$(CC) $(CFLAGS) -o server_inet_udp server_inet_udp.c

client_inet_udp: client_inet_udp.c
		$(CC) $(CFLAGS) -o client_inet_udp client_inet_udp.c

clean:
		rm -f client_loc_udp server_loc_udp server_inet_tcp client_inet_tcp server_loc_tcp client_loc_tcp server_inet_udp client_inet_udp
