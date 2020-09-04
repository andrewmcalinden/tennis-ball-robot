CC = gcc
CFLAGS = -g -Wall

all: server client

server: server.c
	$(CC) $(CFLAGS) -o $@ $<

client: client.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	-rm -f *.o *~ *core* server client
