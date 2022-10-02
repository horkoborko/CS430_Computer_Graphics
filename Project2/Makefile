CC=gcc
CFLAGS=-Wall
LFLAGS = -Wall -c
RM=rm -rf

all: v3test

v3test: v3test.o v3math.o
	$(CC) $(CFLAGS) v3test.o v3math.o -o v3test

v3test.o: v3test.c v3math.h 
	$(CC) $(LFLAGS) v3test.c

v3math.o: v3math.c v3math.h
	$(CC) $(LFLAGS) v3math.c

clean: 
	$(RM) *~ v3test
