#include <iostream>
#include "../motor/motor.h"
#include <wiringPi.h>

using namespace std;

#define LEFTPIN 5
#define RIGHTPIN 6

double Lpower = 0;
double Rpower = 0;

volatile int baseTimeR = 0;
volatile int baseTimeL = 0;

bool lHigh = 1;
bool rHigh = 1;

double superMap(double x, double in_min, double in_max, double out_min, double out_max) 
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void rwmReaderL()
{
    if(digitalRead(LEFTPIN) == 1)
    {
        baseTimeL = micros();
    }

    else
    {
        unsigned int timeGap = micros()-baseTimeL;
        Lpower = superMap(timeGap, 95, 1940, -1, 1);
        
    }

}

void rwmReaderR()
{
    if(digitalRead(RIGHTPIN) == 1)
    {
        baseTimeR = micros();
    }

    else
    {
        unsigned int timeGap = micros()-baseTimeR;        
        Rpower = superMap(timeGap, 95, 1940, -1, 1);
    }

}

int main()
{
    wiringPiSetup();
    pinMode(LEFTPIN, INPUT);
    pinMode(RIGHTPIN, INPUT);

    wiringPiISR (LEFTPIN, INT_EDGE_BOTH, &rwmReaderL);
    wiringPiISR (RIGHTPIN, INT_EDGE_BOTH, &rwmReaderR);

    while (true)
    {
        printf("\nLeft Power:  %.2f", Lpower);
        printf("\nRight Power: %.2f", Rpower);

    }
}

