/*

use softPWM

Generate PWM pulse for servos and dimable LED 


Compile:
  cc -o pwmB pwmB.c  -L/usr/local/lib -lwiringPi

Run:
 sudo ./pwmB


 */


#include <wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main (void) {

  int pin = 17;
  int bright ;
  
  printf ("Raspberry Pi wiringPi PWM test program, pin=%d\n",pin) ;
  
  // Set up the GPIO channels convention
  if (wiringPiSetupGpio () == -1)  exit (1) ;


//int softPwmCreate (int pin, int initialValue, int pwmRange) ;
softPwmCreate (pin,20,100) ;

//void softPwmWrite (int pin, int value) ;
 delay(2000);
 softPwmWrite (pin, 5) ;

 delay(2000);
 softPwmWrite (pin, 10) ;

 delay(2000);
 softPwmWrite (pin, 15) ;

for (;;) delay (1000) ;

	return 0 ;
}
