CC=gcc
CFLAGS=-Wall -I. -std=gnu99 -pedantic -march=native -O2 -Wno-pointer-arith
LDFLAGS=-ljansson
LDFLAGS2=-lpthread


all: meteo

meteo: main.o tcpclient.o configs.o utils.o log.o tcpserver.o meteoserver.o
	$(CC) main.o tcpclient.o configs.o utils.o log.o tcpserver.o meteoserver.o -o meteo $(CFLAGS) $(LDFLAGS) $(LDFLAGS2)

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

tcpserver.o: tcpserver.c
	$(CC) -c tcpserver.c $(CFLAGS) $(LDFLAGS2)

meteoserver.o: meteoserver.c
	$(CC) -c meteoserver.c $(CFLAGS) $(LDFLAGS2)


install:
	-mkdir /usr/share/meteosrv
	-cp /usr/share/meteosrv/meteosrv
	-cp meteosrv.cfg /etc/

remove:
	rm -rf /usr/share/meteosrv
	rm /etc/meteosrv.cfg

clean:
	-rm meteo
	-rm *.o
