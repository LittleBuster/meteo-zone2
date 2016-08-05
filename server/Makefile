CC=gcc
CFLAGS=-Wall -I. -std=gnu99 -pedantic -march=native -O2 -Wno-pointer-arith
LDFLAGS2=-lpthread
LDFLAGS3=-lmysqlclient


all: meteo

meteo: main.o tcpclient.o configs.o utils.o log.o tcpserver.o meteoserver.o database.o
	$(CC) main.o tcpclient.o configs.o utils.o log.o database.o tcpserver.o meteoserver.o -o meteosrv $(CFLAGS) $(LDFLAGS) $(LDFLAGS2) $(LDFLAGS3)

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

database.o: database.c
	$(CC) -c database.c $(CFLAGS) $(LDFLAGS3)


install:
	-mkdir /usr/share/meteosrv
	-cp meteosrv /usr/share/meteosrv/
	-cp meteosrv.cfg /etc/
	-chmod +x /usr/share/meteosrv/meteosrv

remove:
	rm -rf /usr/share/meteosrv
	rm /etc/meteosrv.cfg

clean:
	-rm meteosrv
	-rm *.o
