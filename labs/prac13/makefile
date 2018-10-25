
CC=gcc
CFLAGS=-std=c99 -Wall -Werror

q1 : main.o BSTree.o
	$(CC) -o q1 main.o BSTree.o

main.o : main.c BSTree.h

BSTree.o : BSTree.c BSTree.h

clean :
	rm -f q1 *.o core
