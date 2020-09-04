/*
Basic readout of ADXL345 accelerometer via I2C 

Oryginal code taken from the very bottom of this page:
http://www.raspberrypi.org/forums/viewtopic.php?t=55834

Updated by Jan Balewski, August 2014
*/

#include <assert.h>
#include "ADXL345.h"

//==========================================
//==========================================
bool ADXL345::selectDevice(){
   if (ioctl(fd, I2C_SLAVE, myAddr) < 0) {
      fprintf(stderr, "device ADXL345 not present\n");
      return false;
   }
   return true;
}

//==========================================
//==========================================
bool ADXL345::writeToDevice(char * buf, int len){
   if (write(fd, buf, len) != len)   {
     fprintf(stderr, "Can't write to device ADXL345 buf=%s len=%d\n",fd,buf,len);
     return false;
   }
  return true;
} 


//===============
bool  ADXL345::readXYZ( short &x , short &y, short &z) {
  assert(fd>0); // crash if port was not opened earlier
  if(!selectDevice())   return false;
  //   printf("selectDevice(fd,ADXL345...)  passed\n");
  char buf[7];
  buf[0] = 0x32;     // This is the register we wish to read from
  if(!writeToDevice(buf,2))     return false;
   
  if (read(fd, buf, 6) != 6) {  // Read back data into buf[]
    printf("Unable to read from slave for ADXL345\n");
    return false;
  }  else {
    x = (buf[1]<<8) |  buf[0]; 
    y = (buf[3]<<8) |  buf[2];
    z = (buf[5]<<8) |  buf[4];
  }
  return true;
} 


//==========================================
//==========================================
//==========================================
int ADXL345::init()  {  
  assert(fd>0); // crash if port was not opened earlier
  char buf[6];       // Buffer for data being read/ written on the i2c bus
  
  if(!selectDevice()) return -1;
  
  buf[0] = 0x2d;                   // Commands for performing a ranging
  buf[1] = 0x18;
  
  if(!writeToDevice(buf,2))  return -2;
  
   buf[0] = 0x31;              // Commands for performing a ranging
   buf[1] = 0x0A; //09 4g , A 8g
   
   if(!writeToDevice(buf,2))  return -3;
   printf("ADXL345::init() OK\n");
   return 0; 
}
