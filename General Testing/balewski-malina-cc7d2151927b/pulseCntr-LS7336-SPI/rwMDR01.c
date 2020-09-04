/*
 Dependence: wiringPi

 Author:  Jan Balewski,  December 2015

The default buffer size is 4kB, you need only up to 6B for LS7336 

Compile maually (but Makefile is provided):
  cc -o spi_max187 spi_max197.c  -L/usr/local/lib -lwiringPi

Output prints
 */

#include <wiringPiSPI.h>
  
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

//------ util func returning uchar as binary
const char *byte2bits(int x){
    static char b[9];    b[0] = '\0';
    int z;
    for (z = 128; z > 0; z >>= 1)    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }    return b;
}

//-------- execute cmd w/ 1 byta of I/O data
// global for simplicity
enum { spiChan=0};

unsigned  char  doCmd1B( char * txt, unsigned  char cmd, unsigned  char val){
  enum{ cmdLen=1+1};  // cmd+1B output
  unsigned char cmdL[cmdLen];
  cmdL[0]=cmd;
  cmdL[1]=val;
  int ret=wiringPiSPIDataRW (spiChan, cmdL, cmdLen);
  assert(ret==cmdLen);
  printf("%s  cmd=0x%02x=0b%s --> ans=0x%02x=0b%s\n",txt,cmd,byte2bits(cmd),cmdL[1],byte2bits(cmdL[1]));
  return cmdL[1];
}


//============================
//============================
int main (void) {

  int clk_hz=1* 512*1024;
  printf ("R-Pi w/ wiringPi SPI :chan=%d  clk/kHz=%d \n",spiChan,clk_hz/1024);
  
  if(  wiringPiSPISetup (spiChan, clk_hz)  == -1)  exit (1) ;
  
  printf(" wiringPiSPISetup OK\n");
  unsigned  char cmd,val;

  printf("reading old values from MDR0, MDR1 registers\n");
  cmd=0b01001000 ; val=doCmd1B("rd:MDR0",cmd,0);
  cmd=0b01010000 ; val=doCmd1B("rd:MDR1",cmd,0);
 
  val=0x01;  // b01: 1 count per qudrature cycle
  printf("write 0x%02x to  MDR0  register\n",val);
  cmd=0b10001000 ; val=doCmd1B("wr:MDR0",cmd,val);

  val=0x02;  // b10 : 2 byte depth counter
  printf("write 0x%02x to  MDR1  register\n",val);
  cmd=0b10010000 ; val=doCmd1B("wr:MDR1",cmd,val);

  printf("reading new values from MDR0, MDR1 registers\n");
  cmd=0b01001000 ; val=doCmd1B("rd:MDR0",cmd,0);
  cmd=0b01010000 ; val=doCmd1B("rd:MDR1",cmd,0);
 
  printf("\n --- end \n");
  return 0 ;
}


  /* int wiringPiSPISetup (int channel, int speed) ;
     This is the way to initialise a channel (The Pi has 2 channels; 0 and 1). 
     The speed parameter is an integer in the range 500,000 through 32,000,000 
     and represents the SPI clock speed in Hz.
  */

 /* int wiringPiSPIDataRW (int channel, unsigned char *data, int len) ;
This performs a simultaneous write/read transaction over the selected SPI bus. Data that was in your buffer is overwritten by data returned from the SPI bus.
  */
