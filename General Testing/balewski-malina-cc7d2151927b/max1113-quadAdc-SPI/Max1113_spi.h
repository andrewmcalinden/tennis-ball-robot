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
 * Name        : Max1113_spi.h
 * Original Author      : Jan Balewski
 * Created on  : January 2016
 *
 * Copyright © 2016 Jan Balewski <jan.balewski@gmail.com>
 */

#ifndef _Max1113_spi_H
#define _Max1113_spi_H 

#include <time.h>  // for time measurement

//! Main class that exports selected features for Max1113_spi chip
class Max1113_spi {
  
 public:
  // see Max1113 chip description for explanation
  enum  Reg {CMD_GEN=0x8f }; // read , external clock
  enum  {mxCh=4 }; // number of ADC channels
  
  Max1113_spi(int ch, int clkHz);
  ~Max1113_spi(){ };
  int debug;
  int read(int adcCh);

 private:
  int _spiChan, _spiClockHz;
};

#endif



