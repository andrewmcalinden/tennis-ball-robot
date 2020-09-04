/* 
   Test buzz on pin

Updated by Jan Balewski, April 2015

To check I2C address  

sudo i2cdetect -y 1

*/

#include <stdio.h>
#include <stdlib.h>

#include "Buzz01.h"
#include <wiringPi.h> // my I2C devices:
using namespace std;

//============================================
int main(int argc, char **argv){

  // Set up the GPIO channels convention
  if (wiringPiSetupGpio() == -1)   exit (1);
  
  Buzz01 buz(25);// pin
  buz.doms(50);
  
  buz.do3s();
  
  printf ("\n main END\n");

  return 0;

}



