/*
 * blink.c:
 *      Simple test program to buzz piezzo 

Compile:
  cc -o buzz1 buzz1.c  -L/usr/local/lib -lwiringPi

Run:
 sudo ./buzz1

 */

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

void buzz(int pin,float pitch, float duration){
  float period = 2.0 / pitch;  // period (sec/cyc) is the inverse of the frequency (cyc/sec)
  float delay = period / 2; //calcuate the time for half of the wave
  int  delay_us= delay*1e6;
  int cycles = duration * pitch;  // number of waves to produce is the duration times the frequency

  int i;
  for (i=0; i<cycles; i++ ){ 
    digitalWrite(pin, 1);   
    usleep(delay_us);
    digitalWrite(pin, 0);   
    usleep(delay_us);
  }

}

//===================================
int main (void){
  int pin = 14;
  printf("Raspberry Pi wiringPi piezzo test on pin=%d\n",pin);

  // Set up the GPIO channels convention
  if (wiringPiSetupGpio() == -1)   exit (1);


 
  pinMode(pin, OUTPUT);

  int freq=200; // Hz
  printf("buzz freq/Hz=%d  pin=%d\n",freq,pin);
  buzz(pin,freq,200);
  return 0;
}
