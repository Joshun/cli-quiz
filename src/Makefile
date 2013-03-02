PACKAGE = quiz

CC = gcc

CFLAGS = -Wall -g

all: main

main: main.c file.o question.o
	$(CC) $(CFLAGS) file.o question.o main.c -o ../$(PACKAGE)

question.o: question.c
	$(CC) $(CFLAGS) -c question.c

file.o: file.c
	$(CC) $(CFLAGS) -c file.c

clean:
	rm *.o ../$(PACKAGE)