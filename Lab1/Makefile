all: calc

CC = gcc
CFLAGS = -Wall -Wextra -g

main.o : main.c
	$(CC) -c $(CFLAGS) -o main.o main.c

math.o : math.c math.h
	$(CC) -c $(CFLAGS) -o math.o math.c

calc : main.o math.o 
	$(CC) $(CFLAGS) -o calc main.o math.o

run: calc
	./calc

clean:
	rm -f calc *.o