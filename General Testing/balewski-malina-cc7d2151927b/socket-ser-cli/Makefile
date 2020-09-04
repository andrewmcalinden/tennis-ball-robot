CC = gcc
CFLAGS = -g -Wall

all: server1 client1  server2 client2

server2: server2.cpp JanSocket.h
	$(CC) $(CFLAGS) -o $@ $<

client2: client2.cpp JanSocket.h
	$(CC) $(CFLAGS) -o $@ $<

server1: server1.c
	$(CC) $(CFLAGS) -o $@ $<

client1: client1.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	-rm -f *.o *~ *core* server1 client1 server2 client2
	-rm -rf *.dSYM
