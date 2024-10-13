CC = gcc
CFLAGS = -pthread

all: client_tcp client_udp server_parallel server_parallel_with_pool server_parallel_with_queue server_multiprotocol

client_tcp: client_tcp.c
		$(CC) -o client_tcp client_tcp.c

client_udp: client_udp.c
		$(CC) -o client_udp client_udp.c

server_parallel: server_parallel.c
		$(CC) $(CFLAGS) -o server_parallel server_parallel.c

server_parallel_with_pool: server_parallel_with_pool.c
		$(CC) $(CFLAGS) -o server_parallel_with_pool server_parallel_with_pool.c

server_parallel_with_queue: server_parallel_with_queue.c
		$(CC) $(CFLAGS) -o server_parallel_with_queue server_parallel_with_queue.c

server_multiprotocol: server_multiprotocol.c
		$(CC) -o server_multiprotocol server_multiprotocol.c

clean:
		rm -f client_tcp client_udp server_parallel server_parallel_with_pool server_parallel_with_queue server_multiprotocol
