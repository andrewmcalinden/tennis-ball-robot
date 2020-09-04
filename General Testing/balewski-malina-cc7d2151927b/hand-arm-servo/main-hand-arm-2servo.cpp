/*
testing 2  servos operating a hand-arm mockup
chan=0,1  in PCA9685 servo-16 board connected via I2C bus at 0x40

Updated by Jan Balewski, April 2015

To check I2C address  for servo-16 is 0x40:

sudo i2cdetect -y 1


*/


#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <cmath>

#include "PCA9685.h" // PCA9685 servo-16 board connected via I2C bus at 0x40

#include "Buzz01.h"
#include <wiringPi.h> // my I2C devices:
using namespace std;


#define I2C_FILE_NAME "/dev/i2c-1" // for Rpi B+
enum {Arm=0,Hand, AH};// servo ID for arm & hand
enum {Dw=0,Mid,Up,DMU}; //3 extreme angles of servo 
int main(int argc, char **argv){
  
  // Set up the GPIO channels convention
  if (wiringPiSetupGpio() == -1)   exit (1);  
  Buzz01 buz(25);// pin
  
  
  //  printf ("\n main END\n");
  //--------------
  printf("M: connect to servo16-controller\n");
  int chip_bus=1, chip_addrress=0x40;
  
  int pin[AH]={3,0}; // channels on 16-servo controller
  int domain[AH][DMU];

  domain[Arm][Up]=300;
  domain[Arm][Mid]=250;
  domain[Arm][Dw]=200;

  domain[Hand][Up]=400;
  domain[Hand][Mid]=300;
  domain[Hand][Dw]=200;
 
  PCA9685 servos; // all servos are initialized
  
  servos.init(chip_bus, chip_addrress);
  usleep(100*1000);

  printf ("Setting frequency..\n");
  servos.setPWMFreq (61);
  usleep(1000*1000);

  int mSec=100;
  buz.doms(50);
  printf ("Reset Arm & hand to UP\n");
  for(int k=0;k<AH;k++) {// all servos
    servos.setPWM(pin[k],  domain[k][Up]);    
    usleep(mSec*1000);
  }

  for(int step=0; step<3;step++){
  buz.do3s();

  printf(" forward\n");
  servos.setPWM(pin[Arm],220);
  //usleep(1000*mSec);
  servos.setPWM(pin[Hand],380);
  usleep(1000*1000);
  buz.doms(50);


  if(1){ printf(" touch\n");
  servos.setPWM(pin[Arm],210);
  //usleep(1000*1000);
  servos.setPWM(pin[Hand],320);
  usleep(1000*1000);
  buz.doms(50);
  }


  if(1){ printf(" push\n");
  servos.setPWM(pin[Arm],190);
  //usleep(1000*1000);
  servos.setPWM(pin[Hand],290);
  usleep(1000*1000);
  servos.setPWM(pin[Arm],160);
  usleep(1000*1000);
  }
  //
  // usleep(1000*1000);

  printf ("Reset Arm & hand to UP\n");
  buz.do3s();
  servos.stopPWM(pin[Hand]);// to conserve power
  servos.setPWM(pin[Arm],300);
  usleep(1000*1000);
  servos.setPWM(pin[Hand],400);
  usleep(1000*1000);
  }// end of setps


  for(int k=0;k<16;k++) {// all servos
    servos.stopPWM(k);
  }
  printf ("All servos stop\n");

}



#if 0
  printf ("Testing Arm  servo on pins L=%d\n",pin[Arm]);
  int speed=300;
  while (speed>0) {
    printf(" enter speed:");
    cin>>speed;
    printf(" set speed=%d\n",speed);
    servos.setPWM(pin[Hand],speed);    
    usleep(1000*1000);
  }

#endif
