/*
 Read a pair of 11-bit ADCs from MAX187  via SPI interface
 using some degenrated form of SPI (MOSI is ignored)

 Dependence: wiringPi

 Author:  Jan Balewski,  August 2014

Before you can use SPI interface, you may need to use the gpio utility
 to load the SPI drivers into the kernel :

 gpio load spi

The default buffer size is 4kB, you need only 2B for MAX144,
more details at:
http://wiringpi.com/reference/spi-library/


Compile maually (but Makefile is provided):
  cc -o spi_max187 spi_max197.c  -L/usr/local/lib -lwiringPi

Run:
 sudo ./spi_max187

Output prints

ret=2, dump i:data (hex)
243:0xf3:11110011, 240:0xf0:11110000,  val=3710 hex=e7e  dH=115, dL=30
nL=14 
ret=2, dump i:data (hex)
255:0xff:11111111, 248:0xf8:11111000,  val=4095 hex=fff  dH=127, dL=31
nL=15 

 */

#include <wiringPi.h>

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// util func returning uchar as binary
const char *byte_to_binary(int x){
    static char b[9];
    b[0] = '\0';
    int z;
    for (z = 128; z > 0; z >>= 1)    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }
    return b;
}


//============================
int main (void) {

  enum{ bufLen=2};

  unsigned char data[bufLen];
  int spiChan=0;
  int clk_hz=1* 512*1024;
  printf ("Raspberry Pi wiringPi SPI test program, spi:chan=%d  clk/kHz=%d bufLen/kB=%d\n",spiChan,clk_hz/1024,bufLen/1024) ;

  if(  wiringPiSPISetup (spiChan, clk_hz)  == -1)  exit (1) ;
  /* int wiringPiSPISetup (int channel, int speed) ;
     This is the way to initialise a channel (The Pi has 2 channels; 0 and 1). 
     The speed parameter is an integer in the range 500,000 through 32,000,000 
     and represents the SPI clock speed in Hz.
  */

  printf(" wiringPiSPISetup OK\n");


  /* int wiringPiSPIDataRW (int channel, unsigned char *data, int len) ;
This performs a simultaneous write/read transaction over the selected SPI bus. Data that was in your buffer is overwritten by data returned from the SPI bus.
  */

  int nL=0;
  int ret;
  for (;;)	{
    memset(data,1,sizeof(data)); // clear data buffer
    ret=wiringPiSPIDataRW (spiChan, data, bufLen);
  
    // printf("ret=%d, dump i:data (hex)\n",ret);
    assert(ret==bufLen);
    int i;
    for(i=0;i<-bufLen;i++) {
      printf("%d:0x%x:%s, ",data[i],data[i],byte_to_binary(data[i]));
    }
     
    unsigned char dH,dL;
    
    dH=data[0]&0x7f;
    dL=data[1]>>3;
    int val=dH*32+dL;
    //printf(" val=%d hex=%2x  dH=%d, dL=%d\n",val,val,dH,dL);

    printf("nL=%d val=%d\n",nL,val); nL++; 
      sleep(1); 

    if(nL>15) break;
 }


  printf("\n --- end of buffer\n");
	return 0 ;
}
