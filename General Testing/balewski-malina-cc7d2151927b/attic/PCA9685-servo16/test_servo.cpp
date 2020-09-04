/* 
   Test servo chan=0  in PCA9685 servo-16 board connected via I2C bus at 0x40

 * Original Author      : Georgi Todorov
 * Created on  : Nov 22, 2013
 * Edited by   : Tord Wessman,
 * Edited by   : Jan Balewski, August 2014

To check I2C address  for servo-16 is 0x40:

(on Raspberry Pi B+ type)
sudo i2cdetect -y 1
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
...
30: -- -- -- -- -- -- -- -- -- -- -- UU -- -- -- -- 
40: 40 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
...


*/

#include "PCA9685_pwm.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>

using namespace std;
int main () {
  int chip_bus=1, chip_addrress=0x40;
  int pin=0;
  int pwm_min=160, pwm_max=600;


  printf ("Testing servo on pin=%d\n",pin);
  //make sure you use the right address values.
  PCA9685_pwm pwm;
  
  pwm.init(chip_bus, chip_addrress);
  usleep(1000 * 100);
  printf ("Setting frequency..");
  pwm.setPWMFreq (61);
  usleep(1000 * 1000);

#if 1
  // allow to pick PWM high value
  int speed=300;
  while (speed>0) {
    printf(" enter speed:");
    cin>>speed;
    printf(" set speed=%d\n",speed);
    pwm.setPWM(pin,speed);    
    usleep(1000*1000);
  }
#endif
  
  int count = 0;
  while (count++<1) {
    printf("count=%d\n", count);
    pwm.setPWM(pin,pwm_min);	
    usleep(1000 * 1000);    
    pwm.setPWM(pin,0,pwm_max);    
    usleep(1000 * 1000);
  }

  count = 3;
  while (count++<6) {
    int speed=pwm_min+50*(count-1);
    printf("count=%d speed=%d\n", count,speed);
    pwm.setPWM(pin,0,speed);    
    usleep(2000 * 1000);
  }


  printf ("\n stop this servo");
  pwm.stopPWM(pin);

  return 0;
} 
