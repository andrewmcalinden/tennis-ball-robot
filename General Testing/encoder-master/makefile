GCC=gcc
CFLAGS=-Wall -lwiringPi -lpthread

all: library

library:
	$(GCC) $(CFLAGS) -c encoder.c -o encoder.o

example: library
	$(GCC) $(CFLAGS) example.c encoder.o -o example


clean:
	rm example *.o 
