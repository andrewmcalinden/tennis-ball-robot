/* 
   Test LS7336-based rotary pulse counter using SPI chan0 
   hardawre resolution 400 P/R
   software settings (via registers) :
   - counter depth : 2 bytes
   - 4 pulses per quadrature (aka 1600 pulses per rotation)

   class LS7336 allows:
   int position()
   - computes signed relative rotation. The 2-byte depth allows for
   up to 20 consecutive rotations before counter wraps around
   double procTime(); // sec
   - gives current time since process started with nsec precision
   
 * Name        : test_quadCnt.cpp
 * Original Author      : Jan Balewski
 * Created on  : December 2015
 *
 * Copyright © 2015 Jan Balewski <jan.balewski@gmail.com>
*/

#include "LS7336.h"
#include <stdio.h>
#include <unistd.h> // usleep()
    
using namespace std;
int main () {
  printf("start Jan\n");

  int clk_hz=1* 512*1024;
  int spiChan=0;
  LS7336 pulseCntr(spiChan,clk_hz);
 
  pulseCntr.setCounterDepth(LS7336::cycleX4, LS7336::twoByte);
  pulseCntr.readRegisters(); // for x-check

  pulseCntr.reset();  // uses current position as zero
  //pulseCntr.reset(1400);  // force this cntr offset regardless of current position (rarely used)
  pulseCntr.debug=0;
  
  int offset= pulseCntr.getCntrOffset();
  printf("ZERO position=%d  of %d\n",offset,pulseCntr.maxCntr() );
 
  int delayMsec=200;
  double lastTime=0;
  for(int k=0; ;  k++  ){
    int rotPos=pulseCntr.position();
    double myTime=pulseCntr.procTime();
    printf("k1=%d, pos=%d time=%.4f sec, delT=%.4f sec\n",k,rotPos, myTime, myTime-lastTime);
    lastTime=myTime;
    usleep(delayMsec*1000);
  }

  printf("\n --- end \n");
  return 0 ;
} 
