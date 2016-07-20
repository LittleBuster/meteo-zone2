CC=gcc
CFLAGS=-Wall -I. -std=gnu99 -pedantic -march=native -Wno-pointer-arith


all: test

test: main.o configs.o
	$(CC) main.o configs.o -o test $(CFLAGS)

main.o: main.c
	$(CC) -c main.c $(CFLAGS)

configs.o: ../../pi/configs.c
	$(CC) -c ../../pi/configs.c $(CFLAGS)

clean:
	-rm test
	-rm *.o