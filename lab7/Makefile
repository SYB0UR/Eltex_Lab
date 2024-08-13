all: 
		gcc -c main.c add.c sub.c mul.c div.c
		ar rc libcalc.a add.o sub.o mul.o div.o
		gcc main.o -o calc -L. -lcalc

		rm *.o
