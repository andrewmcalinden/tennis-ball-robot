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
 * Name        : Max1113_spi.cpp
 * Original Author      : Jan Balewski
 * Created on  : January 2016
 *
 * Copyright © 2016 Jan Balewski <jan.balewski@gmail.com>
 */

#include <assert.h>
#include <string.h>
#include <stdio.h>      /* Standard I/O functions *///
#include <wiringPiSPI.h>

#include "Max1113_spi.h"

//=======================
Max1113_spi::Max1113_spi(int ch, int clkHz) {
  assert(ch==0 || ch==1);
  _spiChan=ch;
  _spiClockHz=clkHz;

  printf ("R-Pi w/ wiringPi SPI :chan=%d  clk/kHz=%d \n",_spiChan,_spiClockHz/1024);  
  assert(  wiringPiSPISetup (_spiChan,_spiClockHz)  != -1);
  printf(" wiringPiSPISetup OK for spiChan=%d\n",_spiChan);

}

//=======================
int Max1113_spi::read(int adcChan){
  enum{ bufLen=3}; // up to 3 bytes of output
  unsigned char buf[bufLen];
  memset(buf,0,sizeof(buf));
  assert(adcChan>=0);
  assert(adcChan<mxCh); // limitation of MAX1113
  unsigned  char cmd,ret;  
  int sel2=adcChan%2;
  int  sel1=adcChan/2;
  cmd= ((2*sel2+sel1) <<5) +CMD_GEN;
  //printf( "\nadcChan=%d cmd=0x%02x\n",adcChan,cmd);
  buf[0]=cmd;

  ret=wiringPiSPIDataRW (_spiChan, buf, bufLen);
  //printf("Read ret=%d\n",ret);
  assert(ret==bufLen);
  //data format 0-0-msb-x-x-x-x-x-x-lsb-0-0-0-0-0-0
  int value = (buf[1]<<2) | (buf[2]>>6);
  //printf(" buf[0]=0x%0x resp1,2=0x%02x, 0x%02x\n",buf[0],buf[1],buf[2]);
  //printf(" adc val=%d\n",value);
  return value;


}
 
