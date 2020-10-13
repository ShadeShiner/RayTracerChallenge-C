CC=gcc
CFLAGS=-Wall
LIBS=-lm

tuple: tuple.c tuple.h
	$(CC) $(CFLAGS) -c tuple.c 

canvas: canvas.c
	$(CC) $(CFLAGS) canvas.c -lm tuple.o my_string.o -o canvas


.PHONY: target
clean:
	rm -rf *.o

