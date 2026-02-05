all: gatherer

CC = gcc
CFLAGS = -Wall -Wextra -g -o

gatherer.o: gatherer.c gatherer.h
	$(CC) -c $(CFLAGS) gatherer.o gatherer.c

gatherer: gatherer.o
	$(CC) $(CFLAGS) gatherer gatherer.o

test: gatherer
	./test.sh

run: gatherer
	./gatherer

clean:
	rm -f gatherer gatherer.o

submit:
	submit -c=SI266 -p=milestone01 gatherer.c gatherer.h Makefile test.sh