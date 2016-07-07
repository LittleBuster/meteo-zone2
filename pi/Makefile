CC=gcc
CFLAGS=-Wall -I. -std=gnu99 -pedantic -march=native -O2 -Wno-pointer-arith
LDFLAGS=-ljansson


all: meteo

meteo: main.o dht22.o gpio.o tcpclient.o configs.o
	$(CC) main.o dht22.o gpio.o tcpclient.o configs.o -o meteo $(CFLAGS) $(LDFLAGS)

main.o: main.c
	$(CC) -c main.c $(CFLAGS)

dht22.o: dht22.c
	$(CC) -c dht22.c $(CFLAGS)

gpio.o: gpio.c
	$(CC) -c gpio.c $(CFLAGS)

configs.o: configs.c
	$(CC) -c configs.c $(CFLAGS) $(LDFLAGS)

tcpclient.o: tcpclient.c
	$(CC) -c tcpclient.c $(CFLAGS)


clean:
	-rm meteo
	-rm *.o
