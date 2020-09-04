/*
Utility class to ON/OFF one pin connected to buzzer 
beeping at 4kHz if powered on

*/

#include <wiringPi.h>
#include "Buzz01.h"

//==========================================
//==========================================
Buzz01::Buzz01(int pinx){
  pin=pinx;
  printf("constr Buzz01 pin=%d\n",pin); 
  pinMode(pin, OUTPUT);
}

//==========================================
//==========================================
void Buzz01::dos(int  sec){
  digitalWrite(pin, 1);   
  sleep(sec);
  digitalWrite(pin, 0);   
  
}
//==========================================
//==========================================
void Buzz01::doms(int  msec){
  digitalWrite(pin, 1);   
  usleep(msec*1000);
  digitalWrite(pin, 0);
  usleep(msec*1000);     
}
