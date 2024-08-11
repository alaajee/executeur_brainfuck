CC = gcc
LD = gcc

CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS= -lcriterion

all: brainfuck test

brainfuck: brainfuck_main.o brainfuck_helper.o
	$(CC) $(CFLAGS) $^ -o $@

brainfuck_helper.o : brainfuck_helper.c brainfuck_helper.h

brainfuck_main.o : brainfuck_main.c
	$(CC) $(CFLAGS) -c $< -o $@

test : test1.o test2.o test3.o

test1.o : test1.c brainfuck_helper.c
	$(CC) $(CFLAGS) -c $< -o $@
test2.o : test2.c brainfuck_helper.c
	$(CC) $(CFLAGS) -c $< -o $@
test3.o : test3.c brainfuck_helper.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f brainfuck_main.o brainfuck_helper.o brainfuck_helper brainfuck_main brainfuck  test1 test2 test3 test1.o test2.o test3.o



