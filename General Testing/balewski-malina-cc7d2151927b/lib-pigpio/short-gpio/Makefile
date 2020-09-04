CC=gcc
CFLAGS  += -O3 -Wall -pthread

LL3 =  -lpigpiod_if -pthread -lrt

#rasbian:
#LDFLAGS=-L/usr/local/lib -lwiringPi

#Ubu14
LDFLAGS=-L/usr/local/lib -lpigpiod_if2 -pthread -lrt

ALL = blink_if  servo_if

all:  $(ALL)

blink_if:  blink_if.o
	$(CC) -o   $@ $@.o $(LL3)
	@echo exec:     ./$@

servo_if:  servo_if.o
	$(CC) -o   $@ $@.o $(LL3)
	@echo exec:     ./$@

led1:  led1.c
	$(CC)  $< -o $@ $(LDFLAGS)
	echo exec:  sudo ./$@

clean:
	rm -f *.o *.i *.s *~ $(ALL)

