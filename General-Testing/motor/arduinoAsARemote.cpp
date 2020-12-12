#include <iostream>
#include "motor.h"
#include <wiringPi.h>

using namespace std;

#define LEFTPIN 5
#define RIGHTPIN 6

double Lpower = 0;
double Rpower = 0;
unsigned int timeInit = 0;
unsigned int baseTime = 0;

double superMap(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void rwmReaderLRise(){
    
    baseTime = micros();

    //Lpower = superMap(timeGap, 15, 2036, -1, 1);
    //baseTime = micros();
}
void rwmReaderLFall(){
    printf("\nTHE TIME: %.2f", micros());
    unsigned int timeGap = micros()-baseTime;
    
    printf("\nLEFT: %.2f", Lpower);
    //printf("\nLEFT: %.2f", Lpower);
    Lpower = superMap(timeGap, 15, 2036, -1, 1);
    //baseTime = micros();
}

int main()
{
    wiringPiSetup();

    pinMode(LEFTPIN, INPUT);
    pinMode(RIGHTPIN, INPUT);

    while (true){
        //timeInit = micros(); //gets a time baseline
        //baseTime = micros();
        cout << wiringPiISR (LEFTPIN, INT_EDGE_RISING, &rwmReaderLRise);
        // printf("\nyour and idiot");
        //wiringPiISR (LEFTPIN, INT_EDGE_FALLING, &rwmReaderLFall);
        
        //printf("\nLEFT: %.2f", Lpower);
        //while(digitalRead(LEFTPIN) == 1){}
        //printf("\nTIME:", timeInit);
    }
}

