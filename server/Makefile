CC=gcc
CFLAGS=-Wall -I. -std=gnu99 -pedantic -march=native -O2 -Wno-pointer-arith
LDFLAGS=-lpthread -lmysqlclient


all: meteo

meteo: main.o tcpclient.o configs.o utils.o log.o tcpserver.o meteoserver.o database.o
	$(CC) main.o tcpclient.o configs.o utils.o log.o database.o tcpserver.o meteoserver.o -o meteosrv $(CFLAGS) $(LDFLAGS)

main.o: main.c
	$(CC) -c main.c $(CFLAGS)

configs.o: configs.c
	$(CC) -c configs.c $(CFLAGS)

tcpclient.o: tcpclient.c
	$(CC) -c tcpclient.c $(CFLAGS)

log.o: log.c
	$(CC) -c log.c $(CFLAGS)

utils.o: utils.c
	$(CC) -c utils.c $(CFLAGS)

tcpserver.o: tcpserver.c
	$(CC) -c tcpserver.c $(CFLAGS)

meteoserver.o: meteoserver.c
	$(CC) -c meteoserver.c $(CFLAGS)

database.o: database.c
	$(CC) -c database.c $(CFLAGS)


install:
	-mkdir /usr/share/meteosrv
	-cp meteosrv /usr/share/meteosrv/
	-cp meteosrv.conf /etc/
	-chmod +x /usr/share/meteosrv/meteosrv

remove:
	rm -rf /usr/share/meteosrv
	rm /etc/meteosrv.conf

clean:
	-rm meteosrv
	-rm *.o
