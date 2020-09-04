/*
 * blink.c:
 *      Simple test program to blink an LED on pin 7

Compile:
  cc -o led1 led1.c  -L/usr/local/lib -lwiringPi

Run:
 sudo ./led1

 */



#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
  int pin = 18;
  printf("Raspberry Pi wiringPi blink test on pin=%d\n",pin);

  // Set up the GPIO channels convention
  if (wiringPiSetupGpio() == -1)
    exit (1);

  pinMode(pin, OUTPUT);

  for (;;){
    printf("LED On pin=%d\n",pin);
    digitalWrite(pin, 1);
    delay(250);
    printf("LED Off\n");
    digitalWrite(pin, 0);
    delay(250);
  }

  return 0;
}
