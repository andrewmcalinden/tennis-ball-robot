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
    if(!lHigh)
    {
        baseTimeL = micros();
    }

    else
    {
        unsigned int timeGap = micros()-baseTimeL;
        Lpower = superMap(timeGap, 15, 2041, -1, 1);
    }

    lHigh = !lHigh;
}

void rwmReaderR()
{
    if(!rHigh)
    {
        baseTimeR = micros();
    }

    else
    {
        unsigned int timeGap = micros()-baseTimeR;
        Rpower = superMap(timeGap, 15, 2041, -1, 1);
    }

    rHigh = !rHigh;
}

int main()
{
    wiringPiSetup();
    pinMode(LEFTPIN, INPUT);
    pinMode(RIGHTPIN, INPUT);

    while(digitalRead(LEFTPIN) == 0){}
    wiringPiISR (LEFTPIN, INT_EDGE_BOTH, &rwmReaderL);

    while(digitalRead(RIGHTPIN) == 0){}
    wiringPiISR (RIGHTPIN, INT_EDGE_BOTH, &rwmReaderR);

    while (true)
    {
        printf("\rpower: %.2f", Lpower);

    }
}

