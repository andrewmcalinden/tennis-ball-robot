#include <wiringPi.h>
//#include "encoder.h"
#include "test.h"
#include<iostream>

int position = 0;
unsigned char state = 0;

void update(void)
{
    unsigned char currentState = state & 3;
    if (digitalRead(7))
    {
        currentState |= 4;
    }
    if (digitalRead(0))
    {
        currentState |= 8;
    }

    state = currentState >> 2;

    if (currentState == 1 || currentState == 7 || currentState == 8 || currentState == 14)
    {
        position += 1;
    }
    else if (currentState == 2 || currentState == 4 || currentState == 11 || currentState == 13)
    {
        position -= 1;
    }
    else if (currentState == 3 || currentState == 12)
    {
        position += 2;
    }
    else if (currentState == 6 || currentState == 9)
    {
        position -= 2;
    }
}

void setup()
{
    wiringPiSetup();
    pinMode(7, INPUT);
    pinMode(0, INPUT);

    if (digitalRead(7))
    {
        state |= 1;
    }
    if (digitalRead(0))
    {
        state |= 2;
    }
    wiringPiISR(7, INT_EDGE_BOTH, &update);
    wiringPiISR(0, INT_EDGE_BOTH, &update);
}

int read()
{
    return position;
}

int main()
{
    setup();
    while(true)
    {
        std::cout << read() << "\n";
    }
}