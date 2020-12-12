#include <iostream>
#include "motor.h"
#include <wiringPi.h>

using namespace std;

#define LEFTPIN 5
#define RIGHTPIN 6

double Lpower = 0;
double Rpower = 0;

double superMap(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void rwmReaderL(unsigned int baseTime){
    unsigned int timeGap = micros()-baseTime;
    Lpower = superMap(timeGap, 15, 2036, -1, 1);
}

int main()
{
    wiringPiSetup();

    pinMode(LEFTPIN, INPUT);
    pinMode(RIGHTPIN, INPUT);

    while (true){
        unsigned int timeInit = micros(); //gets a time baseline

        wiringPiISR (LEFTPIN, INT_EDGE_RISING,  rwmReaderL(timeInit));

        printf("\nLEFT: %.2f", Lpower);
        //while(digitalRead(LEFTPIN) == 1){}
        
    }
}

