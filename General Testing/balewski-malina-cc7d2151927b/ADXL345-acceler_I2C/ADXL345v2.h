/*
Basic readout of ADXL345v2 accelerometer via I2C bus

Oryginal code taken from the very bottom of this page:
http://www.raspberrypi.org/forums/viewtopic.php?t=55834

Updated by Jan Balewski, August 2014
*/

#ifndef ADXL345v2_HH
#define ADXL345v2_HH
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


class ADXL345v2 {
 public:
  ADXL345v2 (unsigned char addx=0x53) { devId=addx;} 
  int init(); 
  bool readXYZ(short &ax , short &ay, short &az);
   
 private:
  bool selectDevice();
  bool writeToDevice(char * buf, int len);

  unsigned char devId; // I2C address of the device 
  int fd;// File descriptor
};
#endif
