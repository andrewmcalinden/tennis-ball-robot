#include <iostream>
#include "../motor/motor.h"
#include <wiringPi.h>

using namespace std;

#define LEFTINPUTPIN 5
#define RIGHTINPUTPIN 6

double lPower = 0;
double rPower = 0;

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
    if(digitalRead(LEFTINPUTPIN) == 1)
    {
        baseTimeL = micros();
    }

    else
    {
        unsigned int timeGap = micros()-baseTimeL;
        lPower = superMap(timeGap, 85, 1955, -1, 1);
        if(lPower>-.03 && lPower<.03)
            lPower = 0.0;
    }

}

void rwmReaderR()
{
    if(digitalRead(RIGHTINPUTPIN) == 1)
    {
        baseTimeR = micros();
    }

    else
    {
        unsigned int timeGap = micros()-baseTimeR;        
        rPower = superMap(timeGap, 85, 1955, -1, 1);
        if(rPower>-.03&&rPower<.03)
            rPower = 0.0;
    }

}

int main()
{
    wiringPiSetup();
    pinMode(LEFTINPUTPIN, INPUT);
    pinMode(RIGHTINPUTPIN, INPUT);

    wiringPiISR (LEFTINPUTPIN, INT_EDGE_BOTH, &rwmReaderL);
    wiringPiISR (RIGHTINPUTPIN, INT_EDGE_BOTH, &rwmReaderR);

    while (true)
    {
        printf("\nLeft Power:  %.2f", lPower);
        printf("\nRight Power: %.2f", rPower);

    }
}

