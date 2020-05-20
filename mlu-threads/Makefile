pmms: main.o read.o thread.o
	gcc main.o read.o thread.o -o pmms -lrt -pthread

main.o: main.c read.h thread.h
	gcc -c main.c
read.o: read.c read.h
	gcc -c read.c
thread.o: thread.c thread.h read.h
	gcc -c thread.c

clean:
	rm -f main.o read.o thread.o pmms
	
