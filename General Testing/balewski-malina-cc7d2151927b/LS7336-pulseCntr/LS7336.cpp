/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * Name        : LS7336.cpp
 * Original Author      : Jan Balewski
 * Created on  : December 2015
 *
 * Copyright © 2015 Jan Balewski <jan.balewski@gmail.com>
 */

#include <assert.h>//tmp
#include <stdio.h>      /* Standard I/O functions *///
#include <string.h> // strcat
#include <wiringPiSPI.h>

#include "LS7336.h"

//=======================
LS7336::LS7336(int ch, int clkHz) {
  _spiChan=ch;
  _spiClockHz=clkHz;

  printf ("R-Pi w/ wiringPi SPI :chan=%d  clk/kHz=%d \n",_spiChan,_spiClockHz/1024);  
  assert(  wiringPiSPISetup (_spiChan,_spiClockHz)  != -1);
  printf(" wiringPiSPISetup OK\n");

}

//------ util func returning uchar as binary
//=======================
const char *LS7336::byte2bits(int x){ 
  static char b[9];    b[0] = '\0';
  int z;
  for (z = 128; z > 0; z >>= 1)    {
    strcat(b, ((x & z) == z) ? "1" : "0");
  }    return b;
}

//=======================
double LS7336::procTime(){
  if ( clock_gettime( CLOCK_REALTIME, &tp2) == -1 ) {
    perror( "clock get time 2" ); 
    assert(33==67);
  }
  
  // this way assures fractional seconds are accounted properly
  double tRel=tp2.tv_sec-tp1.tv_sec; // units are sec
  tRel+=(tp2.tv_nsec- tp1.tv_nsec)*1.e-9; // units were in nsec
  return tRel;
}


//---------  core functions
//=======================
void LS7336::readRegisters(){
  unsigned  char cmd,nw=2,ret;
  Reg regL[]={MDR0,MDR1,STR};
  const char *nameL[]={"MDR0","MDR1","STR "};

  for(int ir=0;ir<3;ir++){
    buf[0]=cmd=(LS7336::RD<<6) + (regL[ir]<<3); 
    ret=wiringPiSPIDataRW (_spiChan, buf, nw);
    assert(ret==nw);
    printf("Read reg=%s count/quadrature: cmd=0x%02x  val=0x%02x==0b%s\n",nameL[ir],cmd,  buf[1],byte2bits(buf[1]));
  }
}


//=======================
void LS7336::setCounterDepth(CountMode factor, CounterDepth depth) {
  unsigned  char cmd,val,nw=2,ret;

  // MDR0 register - set couts per cycle
  buf[0]=cmd=(LS7336::WR<<6) + (LS7336::MDR0<<3);
  buf[1]=val=factor;
  if(debug) printf("Set MDR0 count/quadrature: cmd=0x%02x=0b%s  val=0x%02x\n",cmd,byte2bits(cmd),val);
  ret=wiringPiSPIDataRW (_spiChan, buf, nw);
  assert(ret==nw);
 

  // MDR1 register - set conter depth
  cntrDepth=depth-LS7336::fourByte;
  cntrMaxVal=(1<<8*cntrDepth)-1;
  cntrHighVal=cntrMaxVal/2;
  buf[0]=cmd=(LS7336::WR<<6) + (LS7336::MDR1<<3);
  buf[1]=val=depth;
  if(debug) printf("Set MDR1 counter depth=%d : cmd=0x%02x=0b%s  val=0x%02x\n",cntrDepth,cmd,byte2bits(cmd),val);
  ret=wiringPiSPIDataRW (_spiChan, buf, nw);
  assert(ret==nw);
}


//=======================
int LS7336::position(){
  int absPos=readPhysicalCntr()-cntrOffset;
  // handle wrap-around
  if (absPos < -cntrHighVal )
    absPos+=cntrMaxVal;
  else if (absPos > cntrHighVal )
    absPos-=cntrMaxVal;
   //printf("n=%d nPulses=%d\n",n,nPulses);
  //    printf("n=%d relPulses=%d  Min/Max=%d,%d   avrAmpl=%d delAmpl=%d\n",n  ,relPulses ,minCnt,maxCnt, (-minCnt+maxCnt)/2,minCnt+maxCnt);
 
}


//=======================
void LS7336::reset(int offset){
  cntrOffset=offset;
  int curCnt=readPhysicalCntr();
  printf("LS7336  is set with cntOff=%d at curCnt=%d\n",cntrOffset,curCnt);
   if ( clock_gettime( CLOCK_REALTIME, &tp1) == -1 ) {
      perror( "clock get time 1" ); 
      assert(11==34);
    }
   //printf( "#Current time (since 1970) is %d sec %d nsec \n",tp1.tv_sec, tp1.tv_nsec);
}


//=======================
void LS7336::reset(){
  reset(readPhysicalCntr());
}



//=======================
  int LS7336::readPhysicalCntr(){
  assert( cntrDepth>0);
  unsigned  char nw=1+cntrDepth,ret;

  // parallel transfer of CNTR to ORT
  buf[0]=(LS7336::LOAD<<6) + (LS7336::OTR<<3);
  ret=wiringPiSPIDataRW (_spiChan, buf, 1);
  assert(ret==1);
  
  // serail readout of OTR
  buf[0]=(LS7336::RD<<6) + (LS7336::CNTR<<3);
  ret=wiringPiSPIDataRW (_spiChan, buf, nw);
  assert(ret==nw);

  int sum=0;
  if(debug) printf ("   rd-data OTR:\n");
  int i;
  // buf[1]=0xff;buf[2]=2;
  for (  i=0; i<cntrDepth; i++){
    int oneByte=buf[i+1];
    sum+= oneByte<<(cntrDepth-1-i)*8;
    if(debug) printf(" OTR i=%d  val=%d=0b%s  sum=%d\n",i, oneByte,byte2bits(oneByte),sum); 
  }
  if(debug) printf("\n");
  return sum;
}
  


