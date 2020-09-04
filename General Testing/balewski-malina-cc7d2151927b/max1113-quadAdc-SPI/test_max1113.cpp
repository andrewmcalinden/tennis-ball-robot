/* 
   Test Max1113_spi - quad ADC, 8-bit
   
 * Name        : test_quadCnt.cpp
 * Original Author      : Jan Balewski
 * Created on  : December 2015
 *
 * Copyright © 2015 Jan Balewski <jan.balewski@gmail.com>
*/

#include "Max1113_spi.h"
#include <stdio.h>
#include <unistd.h> // usleep()
    
using namespace std;
int main () {
  printf("start Max1113 readout\n");

  int clk_hz=500*1000; // Max1113 wants 500kHz
  int spiChan=1; // allowed  CE0=0, CE1=1
  Max1113_spi adcChip(spiChan,clk_hz);

  int adcChan=2;
  // int val=adcChip.read(adcChan);
  //printf(" read ADC(ch=%d spi=%d)=%d\n\n", adcChan, spiChan,val);

  for(adcChan=0; adcChan<4; adcChan++){
    int val=adcChip.read(adcChan);
    printf(" read(ch=%d spi=%d)  ADC=%d\n\n", adcChan, spiChan,val);
    usleep(100*1000);

  }

  adcChan=2;
  int delayMsec=200;
  for(int k=0; ;  k++  ){
    int val=adcChip.read(adcChan);
    printf("%d read(ch=%d)  ADC=%d\n", k, adcChan,val);
    usleep(500*1000);
  }

  printf("\n --- end \n");
  return 0 ;
} 
