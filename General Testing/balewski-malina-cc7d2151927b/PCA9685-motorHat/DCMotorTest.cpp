/*  This is test program driving DC motor connected to 
    Adafruit Motor Shield V2 for Arduino.

    It uses signal to capture ctrl-c  and turn of PWM 
    even if program gets aborted by the operator
*/

#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "PCA9685_motorHat.h"

Adafruit_DCMotor *myMotor=0;

void my_handler(sig_t s){
  printf("my handler caught signal %d  p=%p\n",(int)s,myMotor);
  printf("emergency stop motor\n");
  myMotor->run(RELEASE);
  exit(1); 
}

//=================================
//=================================
int main(int argc, char **argv){
  printf("DCMotorTest-MAIN\n");

  signal (SIGINT,(__sighandler_t)my_handler);
  printf("Note, you can press ctrl-c to kill it and motor will by truned off safely by the signal handler\n");


  // Create the motor shield object with the default I2C address
  PCA9685_motorHat AFMS = PCA9685_motorHat((uint8_t)0x60); 

  printf("Adafruit Motorshield v2 - poke DC Motor test!\n");

  AFMS.begin(1600);  // create with the default frequency 1.6KHz
  
  // Select which 'port' M1, M2, M3 or M4. In this case, M1
  myMotor= AFMS.getMotor(1);

  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(150);
  myMotor->run(FORWARD);
  // turn off motor
  myMotor->run(RELEASE);

  int i;  
  printf("tick\n");
  myMotor->run(FORWARD);
  for (i=0; i<255; i++) {
    myMotor->setSpeed(i);  
    usleep(10*1000); // u-sec
  }

  for (i=255; i!=0; i--) {
    myMotor->setSpeed(i);  
    usleep(10*1000);
  }
  
  printf("tock\n");
  
  myMotor->run(BACKWARD);
  for (i=0; i<255; i++) {
    myMotor->setSpeed(i);  
    usleep(10*1000);
  }
  for (i=255; i!=0; i--) {
    myMotor->setSpeed(i);  
    usleep(10*1000);
  }

  printf("end stop motor\n");
  myMotor->run(RELEASE);
  usleep(1000*1000);
}
