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
 * Name        : LS7336.h
 * Original Author      : Jan Balewski
 * Created on  : December 2015
 *
 * Copyright © 2015 Jan Balewski <jan.balewski@gmail.com>
 */

#ifndef _LS7336_H
#define _LS7336_H 
#include <inttypes.h> // symilar to Root _t-types
#include <time.h>  // for time measurement

//! Main class that exports selected features for LS7336 chip
class LS7336 {
  
 public:
  // see LS7366 chip description for explanation
  enum  Reg {MDR0=0b001, MDR1, DTR, CNTR,OTR,STR}; 
  enum  Ops {CLR=0b00, RD, WR, LOAD};
  enum  CounterDepth {fourByte=0,threeByte, twoByte, oneByte};
  enum  CountMode {cycleX1=1, cycleX2, cycleX4};
  
  LS7336(int ch, int clkHz);
  virtual ~LS7336(){ debug=1; cntrDepth=0; };
  int debug;
  void setCounterDepth(CountMode factor, CounterDepth depth);
  void readRegisters();
  int position();
  const char *byte2bits(int x);  // auxilliary
  int maxCntr(){ return cntrMaxVal;} // auxilliary
  void reset(); // resets sofftware offset to current physical position
  void reset(int offset); // use this offset regardless of current position
  void setPWMFreq(int){};
  int  getCntrOffset(){ return cntrOffset;} // auxilliary
  double procTime(); // sec

 private:
  int _spiChan, _spiClockHz;
  int cntrDepth, cntrOffset, cntrHighVal,  cntrMaxVal;
  struct timespec tp1, tp2;
  enum{ bufLen=6}; // up to 5 bytes of output
  unsigned char buf[bufLen];
  int readPhysicalCntr(); 
};

#endif



