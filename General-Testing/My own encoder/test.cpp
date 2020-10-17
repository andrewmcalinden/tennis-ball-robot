#include <wiringPi.h>
//#include "encoder.h"
#include<iostream>

int position;
unsinged char state;

    void
    setup()
{
    wiringPiSetup();
    pinMode(7, INPUT);
    pinMode(0, INPUT);

    position = 0;
    state = 0;

    if (digitalRead(pinA))
    {
        state |= 1;
    }
    if (digitalRead(pinB))
    {
        state |= 2;
    }
    wiringPiISR(pinA, INT_EDGE_BOTH, &update);
    wiringPiISR(pinB, INT_EDGE_BOTH, &update);
}


void update(void)
{
    unsigned char currentState = state & 3;
    if (digitalRead(pinA))
    {
        currentState |= 4;
    }
    if (digitalRead(pinB))
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

int read()
{
    return position;
}

int main()
{
    setup();
    while(true)
    {
        std::cout << enc.read() << "\n";
    }
}