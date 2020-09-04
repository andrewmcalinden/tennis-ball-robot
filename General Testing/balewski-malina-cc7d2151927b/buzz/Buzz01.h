/*
Utility class to ON/OFF one pin connected to buzzer 
beeping at 4kHz if powered on

Updated by Jan Balewski, August 2014

Test code:
  // Set up the GPIO channels convention
  if (wiringPiSetupGpio() == -1)   exit (1);

  Buzz01 buz(12); // pin
  buz.dos(2); // beep N seconds
  sleep(1);
  buz.doms(200); // beep N mili-seconds
  sleep(1);
  buz.doms(100);
  return 0;


*/

#ifndef BUZZ01_HH
#define BUZZ01_HH
#include <stdio.h>
#include <unistd.h>


class Buzz01 {
 public:
  Buzz01(int pinx);
  void dos(int  sec);// beep for N seconds
  void doms(int  msec);// beep for N mili-seconds
  void do2s(){ doms(50); doms(50); }
  void do3s(){ doms(50); doms(50); doms(50); }

 private:
  int pin;

};

#endif
