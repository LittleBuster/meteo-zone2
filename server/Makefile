CC=gcc
CFLAGS=-Wall -I. -std=gnu99 -pedantic -march=native -O2 -Wno-pointer-arith
LDFLAGS=-ljansson


all: meteo

meteo: main.o tcpclient.o configs.o utils.o log.o
	$(CC) main.o tcpclient.o configs.o utils.o log.o -o meteo $(CFLAGS) $(LDFLAGS)

main.o: main.c
	$(CC) -c main.c $(CFLAGS)

configs.o: configs.c
	$(CC) -c configs.c $(CFLAGS) $(LDFLAGS)

tcpclient.o: tcpclient.c
	$(CC) -c tcpclient.c $(CFLAGS)

log.o: log.c
	$(CC) -c log.c $(CFLAGS)

utils.o: utils.c
	$(CC) -c utils.c $(CFLAGS)


clean:
	-rm meteo
	-rm *.o
