CC=gcc
CFLAGS=-Wall -I. -std=gnu99 -pedantic -march=native -O2 -Wno-pointer-arith -Wno-address


all: meteo

meteo: main.o dht22.o gpio.o tcpclient.o configs.o utils.o log.o checker.o
	$(CC) main.o dht22.o gpio.o tcpclient.o configs.o utils.o log.o checker.o -o meteo $(CFLAGS)

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

log.o: log.c
	$(CC) -c log.c $(CFLAGS)

utils.o: utils.c
	$(CC) -c utils.c $(CFLAGS)

checker.o: checker.c
	$(CC) -c checker.c $(CFLAGS)


install:
	mkdir /usr/share/meteo
	cp meteo.conf /etc/
	cp meteo /usr/share/meteo/
	chmod +x /usr/share/meteo/meteo

remove:
	rm -rf /usr/share/meteo/
	rm /etc/meteo.conf

clean:
	-rm meteo
	-rm *.o
