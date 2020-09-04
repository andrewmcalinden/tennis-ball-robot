/*
Basic readout of ADXL345 accelerometer via I2C 

Oryginal code taken from the very bottom of this page:
http://www.raspberrypi.org/forums/viewtopic.php?t=55834

Updated by Jan Balewski, August 2014

To check I2C address is 0x53:

sudo i2cdetect -y 1
pi@raspberrypi ~/testADXL345 $ sudo i2cdetect -y 1
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:          -- -- -- -- -- -- -- -- -- -- -- -- -- 
...
50: -- -- -- 53 -- -- -- -- -- -- -- -- -- -- -- -- 
...
70: -- -- -- -- -- -- -- --        

Compile manually (but Makefile is provided)
  g++ -o test_ADXL345 ADXL345.cpp test_ADXL345.cpp   

Run:
 sudo ./test_ADXL345

Output:
Opened i2c control file, id=3
ADXL345::init() OK
k=  1  acceleration (a.u.)  mag=272.0    ax,ay,az=-43, 18, -268
k=  2  acceleration (a.u.)  mag=274.8    ax,ay,az=-42, 18, -271
k=  3  acceleration (a.u.)  mag=273.8    ax,ay,az=-42, 18, -270
k=  4  acceleration (a.u.)  mag=272.8    ax,ay,az=-42, 17, -269
...

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
#include "ADXL345.h"
using namespace std;

#define I2C_FILE_NAME "/dev/i2c-1" // for Rpi B+

int main(int argc, char **argv){
  
  // Open a connection to the I2C userspace control file.
  int i2c_fd=i2c_fd = open(I2C_FILE_NAME, O_RDWR);
  if (i2c_fd < 0) {
    printf("Unable to open i2c control file, err=%d\n",i2c_fd);
    exit(1);
  }
  printf("Opened i2c control file, id=%d\n",i2c_fd);


  ADXL345 myAcc(i2c_fd);
  int ret=myAcc.init();
  if(ret)  {
    printf("failed init ADXL345, ret=%d\n",ret); exit(1);
  }
  usleep(100*1000);

  int k=0;
  short ax,ay,az;
  while(myAcc.readXYZ(ax,ay,az)) {
     k++;

     float aa=ax*ax+ay*ay+az*az;
     float a=sqrt(aa);
     printf("k=%3d  acceleration (a.u.)  mag=%.1f    ax,ay,az=%d, %d, %d\n",k,a,ax,ay,az);

     usleep(500*1000);   
   }

   return 0;
}
