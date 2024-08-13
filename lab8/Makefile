all:
		gcc -fPIC -c add.c sub.c mul.c div.c
		gcc -shared -o libcalc.so.0.0.0 add.o sub.o mul.o div.o -Wl,-soname,libcalc.so.0
		ln -s libcalc.so.0.0.0 libcalc.so.0
		ln -s libcalc.so.0.0.0 libcalc.so
		gcc main.c -o calc -L. -lcalc -Wl,-rpath,.
		rm *.o
