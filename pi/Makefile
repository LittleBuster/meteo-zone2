CC=gcc
CFLAGS=-Wall -I. -std=gnu99 -pedantic -march=native
LDFLAGS=


all: meteo

meteo: main.o dht22.o gpio.o
	$(CC) main.o dht22.o gpio.o -o meteo $(CFLAGS)

main.o: main.c
	$(CC) -c main.c $(CFLAGS)

dht22.o: dht22.c
	$(CC) -c dht22.c $(CFLAGS)

gpio.o: gpio.c
	$(CC) -c gpio.c $(CFLAGS)


clean:
	-rm meteo
	-rm *.o