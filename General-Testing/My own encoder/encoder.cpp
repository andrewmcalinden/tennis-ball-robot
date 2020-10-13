#include "encoder.h"
Encoder::Encoder(int pinALoc, int pinBLoc)
    :pinA{pinALoc}, pinB{pinBLoc}
{
    wiringPiSetup();
    pinMode(pinA, INPUT);
    pinMode(pinB, INPUT);

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

void Encoder::update()
{
    
}
