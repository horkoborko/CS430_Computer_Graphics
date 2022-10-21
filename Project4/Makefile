CC=gcc
CFLAGS=-Wall
RM=rm -rf

all: raycast

raycast: raycast.c ppmrw.c ppmrw.h v3math.c v3math.h
	$(CC) $(CFLAGS) raycast.c v3math.c ppmrw.c -o raycast

clean:
	$(RM) *~ *.o raycast
