all: parser practicum

practicum: practicum.c
	gcc -Wall -g -o practicum practicum.c -lm

parser: parser.c
	gcc -Wall -g -o parser parser.c

run: parser
	./parser

clean:
	rm -f parser practicum
