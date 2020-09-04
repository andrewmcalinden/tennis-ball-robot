/*
  use of the function softToneWrite which oscillates the selected pin at a given frequency. The example program causes the piezo element to play a scale. 

Compile:
  cc -o softTone softTone.c  -L/usr/local/lib -lwiringPi

Run:
 sudo ./softTone


 */


#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
 
#include <wiringPi.h>
#include <softTone.h>
 
#define PIN 17
 
int scale [23] = { 659, 659, 0, 659, 0, 523, 659, 0, 784, 0,0,0, 392, 0,0,0, 523, 0,0, 392, 0,0,330 } ;
 
int main ()
{
  int i ;
  // Set up the GPIO channels convention
  wiringPiSetupGpio() ;
  softToneCreate (PIN) ;


  // one continnous tone
  // softToneWrite (PIN, 1000) ;  delay (200000) ;  exit(1);


  for (i = 0 ; i < 23 ; ++i)
    {
      printf ("%3d freq=%d\n", i,  scale [i]) ;
      softToneWrite (PIN, scale [i]) ;
      delay (200) ;
    }
}
