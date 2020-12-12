#include <iostream>
#include "motor.h"
#include <wiringPi.h>

using namespace std;

#define LEFTPIN 5
#define RIGHTPIN 6

double superMap(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main()
{
    wiringPiSetup();

    pinMode(LEFTPIN, INPUT);
    pinMode(RIGHTPIN, INPUT);

    while (true){
        unsigned int timeInit = micros(); //gets a time baseline

        while(digitalRead(LEFTPIN) == 0){} //waits until pin goes high

        unsigned int timeGap = micros()-timeInit; //measures time of cycle
        double Lpower = timeGap; //sets power
        //double Lpower = 2*((timeGap/2041.0)-.5); //sets power
        printf("\nLEFT: %.2f", Lpower);
        while(digitalRead(LEFTPIN) == 1){}
        
    }
}

