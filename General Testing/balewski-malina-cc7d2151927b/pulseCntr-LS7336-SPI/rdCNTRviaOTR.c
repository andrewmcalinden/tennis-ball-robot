/*

Reads pulse counter  LS7336   in infinite loop
 Dependence: wiringPi

 Author:  Jan Balewski,  December 2015

Typical output

n=118 relPulses=128  Min/Max=-144,139   avrAmpl=141 delAmpl=-5
n=119 relPulses=123  Min/Max=-144,139   avrAmpl=141 delAmpl=-5
n=120 relPulses=117  Min/Max=-144,139   avrAmpl=141 delAmpl=-5
n=121 relPulses=111  Min/Max=-144,139   avrAmpl=141 delAmpl=-5
n=122 relPulses=103  Min/Max=-144,139   avrAmpl=141 delAmpl=-5
n=123 relPulses=95  Min/Max=-144,139   avrAmpl=141 delAmpl=-5
n=124 relPulses=86  Min/Max=-144,139   avrAmpl=141 delAmpl=-5

*/

#include <wiringPiSPI.h>
  
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

//-------- execute cmd w/ 1 byta of I/O data
// global for simplicity
enum { spiChan=0};
enum {numWord=2}; // 2x8 bit counter depth
int dbg=1;
int delayMsec=20;

//============================
unsigned  char  doCmd1B( char * txt, unsigned  char cmd, unsigned  char val){
  enum{ cmdLen=1+1};  // cmd+1B output
  unsigned char cmdL[cmdLen];
  cmdL[0]=cmd;
  cmdL[1]=val;
  int ret=wiringPiSPIDataRW (spiChan, cmdL, cmdLen);
  assert(ret==cmdLen);
  if(dbg)
    printf("%s  cmd=0x%02x --> ans=0x%02x\n",txt,cmd,cmdL[1]);
  return cmdL[1];
}

//============================
int readOTR() { // reads OTR to which CNTR was parallel-copied
  unsigned  char cmd=0b11101000 ; doCmd1B("load:OTR",cmd,0);
  enum{ cmdLen2=1+numWord};  // cmd+1B output
  unsigned char cmdL[cmdLen2];
  cmdL[0]=0b01101000; // txt="rd:OTR";
  //cmdL[0]=0b01100111; // txt="rd:CNTR";
  int ret=wiringPiSPIDataRW (spiChan, cmdL, cmdLen2);
  assert(ret==cmdLen2);
  int sum=0;
  //print "   rd-data:",
  int i;
  for (  i=0; i<numWord; i++){
    int oneByte=cmdL[i+1];
    //print "0x%0X=%s  "%(resp[i+1],format( resp[i+1],'08b') ),
    sum+= oneByte<<(numWord-1-i)*8;
  }
  //print ""
  return sum;
}


//============================
//============================
int main (void) {

  int clk_hz=1* 512*1024;
  printf ("R-Pi w/ wiringPi SPI :chan=%d  clk/kHz=%d \n",spiChan,clk_hz/1024);  
  if(  wiringPiSPISetup (spiChan, clk_hz)  == -1)  exit (1) ;  
  printf(" wiringPiSPISetup OK\n");

  //tmp  float delT=10;  // miliseconds


  unsigned  char cmd,val;

  // setting registers to
  printf( "reading numWord=%d and 2*400 counts per 360 deg\n",numWord);
  /* MDR0 register meaning
  b01: 1 counts per qudrature cycle
  b10: 2 counts per qudrature cycle
  b11: 4 counts per qudrature cycle
  */

  val=0x03; 
  printf("write 0x%02x to  MDR0  register\n",val);
  cmd=0b10001000 ; val=doCmd1B("wr:MDR0",cmd,val);

  
  /*  MDR1 register meaning
   b00 : 4 byte depth counter
   b10 : 2 byte depth counter
  */
  val=0x02; 
  printf("write 0x%02x to  MDR1  register\n",val);
  cmd=0b10010000 ; val=doCmd1B("wr:MDR1",cmd,val);

  printf("reading back values from MDR0, MDR1 registers\n");
  cmd=0b01001000 ; val=doCmd1B("rd:MDR0",cmd,0);
  cmd=0b01010000 ; val=doCmd1B("rd:MDR1",cmd,0);
 
  printf("\n start loop of reading CNT via OTR \n");

  dbg=0; // disable extra printing
  // reading current counter and set is as zero:
  // copy CNTR to OTR

  int nPulses0= readOTR();
  printf ("starting counter value=%d",nPulses0);

  int n=0;
  int mxUint16=65535;
  int minCnt=0, maxCnt=0;


  while (1) {
    int nPulses= readOTR();
    n++;
    int relPulses=  nPulses-nPulses0;
    if (relPulses < -mxUint16/2 )
      relPulses+=mxUint16;
    else if ( relPulses > mxUint16/2 )
      relPulses-=mxUint16;

    if (minCnt>relPulses)
      minCnt=relPulses;
    if (maxCnt<relPulses)
      maxCnt=relPulses;
    //printf("n=%d nPulses=%d\n",n,nPulses);
    printf("n=%d relPulses=%d  Min/Max=%d,%d   avrAmpl=%d delAmpl=%d\n",n  ,relPulses ,minCnt,maxCnt, (-minCnt+maxCnt)/2,minCnt+maxCnt);
    delay(delayMsec);
  }

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
