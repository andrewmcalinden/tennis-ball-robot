/*
 Read a pair of 11-bit ADCs from MAX144  via SPI interface
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
  cc -o spi_max144 spi_max144.c  -L/usr/local/lib -lwiringPi

Run:
 sudo ./spi_max144

Output prints pairs of ADC for chan0, & chan1, pause 2 seconds
224:0xe0:11100000, 126:0x7e:01111110,  chan=0  val=126
255:0xff:11111111, 242:0xf2:11110010,  chan=1  val=2034

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
  int ab=0; // to sleep only every other readout
  for (;;)	{
    memset(data,1,sizeof(data)); // clear data buffer
    ret=wiringPiSPIDataRW (spiChan, data, bufLen);
    ab=!ab;
    // printf("ret=%d, ab=%d dump i:data (hex)\n",ret,ab);
    assert(ret==bufLen);
    int i;
    for(i=0;i<-bufLen;i++) {
      printf("%d:0x%x:%s, ",data[i],data[i],byte_to_binary(data[i]));
    }
     
    unsigned char chan,dH,dL;
    chan=(data[0]>>4)&0x1;
    dH=data[0]&0x7;
    int val=dH*256+data[1];
    printf(" chan=%d  val=%d\n",chan,val);

    // dealy is below
    if(ab==0) { 
      printf("nL=%d \n",nL); nL++; 
      sleep(1); 
    }
    if(nL>5) break;
 }


  printf("\n --- end of buffer\n");
	return 0 ;
}
