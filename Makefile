########################## Makefile #######################
PROGRAM=./bs

all: $(PROGRAM)
bs: bs.o main.o 
	gcc -o bs bs.o main.o
bs.o: bs.c
	gcc -o bs.o -c bs.c -Wall 
main.o: main.c bs.h
	gcc -o main.o -c main.c -Wall
clean:
	rm -f *.o main $(PROGRAM) 