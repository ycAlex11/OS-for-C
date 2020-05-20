pmms: main.o read.o process.o
	gcc main.o read.o process.o -o pmms -lrt -pthread

main.o: main.c read.h process.h
	gcc -c main.c
read.o: read.c read.h
	gcc -c read.c
process.o: process.c process.h
	gcc -c process.c

clean:
	rm -f main.o read.o process.o pmms
	
