CC=gcc
CFLAGS=-Wall -I. -std=gnu99 -pedantic -march=native -Wno-pointer-arith


all: keys

keys: main.o
	$(CC) main.o -o genkey $(CFLAGS)

main.o: main.c
	$(CC) -c main.c $(CFLAGS)

clean:
	-rm genkey
	-rm *.o
