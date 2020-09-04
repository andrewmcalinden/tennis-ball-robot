CC=cc

#rasbian:
#LDFLAGS=-L/usr/local/lib -lwiringPi

#Ubu14
LDFLAGS=-L/usr/local/lib -lwiringPi -lpthread

all:  buzz1 led1

buzz1:  buzz1.c
	$(CC)  $< -o $@ $(LDFLAGS)
	echo exec:  sudo ./$@

led1:  led1.c
	$(CC)  $< -o $@ $(LDFLAGS)
	echo exec:  sudo ./$@

clean:
	rm -f buzz1  led1
