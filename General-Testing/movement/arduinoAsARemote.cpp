#include <iostream>
#include "../motor/motor.h"
#include <wiringPi.h>

using namespace std;

#define LEFT_INPUT_PIN 5
#define RIGHT_INPUT_PIN 6

#define DIRECTION_PIN_FORWARD_LEFT 22
#define POWER_PIN_LEFT 23
#define DIRECTION_PIN_FORWARD_RIGHT 27
#define POWER_PIN_RIGHT 26

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
    if(digitalRead(LEFT_INPUT_PIN) == 1)
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
    if(digitalRead(RIGHT_INPUT_PIN) == 1)
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

    Motor motorL(DIRECTION_PIN_FORWARD_LEFT, POWER_PIN_LEFT);
    Motor motorR(DIRECTION_PIN_FORWARD_RIGHT, POWER_PIN_RIGHT);

    pinMode(LEFT_INPUT_PIN, INPUT);
    pinMode(RIGHT_INPUT_PIN, INPUT);

    wiringPiISR (LEFT_INPUT_PIN, INT_EDGE_BOTH, &rwmReaderL);
    wiringPiISR (RIGHT_INPUT_PIN, INT_EDGE_BOTH, &rwmReaderR);

    while (true)
    {
        motorL.setPower(lPower);
        motorR.setPower(rPower); 
    }
}

