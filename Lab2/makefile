all: part1 part2

CC = gcc
CFLAGS = -Wall -Wextra -g

part1.o: part1.c student.h
	$(CC) -c $(CFLAGS) -o part1.o part1.c

part1: part1.o
	$(CC) $(CFLAGS) -o part1 part1.o

part2.o: part2.c student.h
	$(CC) -c $(CFLAGS) -o part2.o part2.c

part2: part2.o
	$(CC) $(CFLAGS) -o part2 part2.o

run: part2
	./part2

clean:
	rm -f part1 part2 *.o