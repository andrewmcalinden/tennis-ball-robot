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
    unsigned char state = this->state & 3;
    if (digitalRead(pinA))
    {
        state |= 4;
    }
    if (digitalRead(pinB))
    {
        state |= 8;
    }

    this->state = state >> 2;

    if (state == 1 || state == 7 || state == 8 || state == 14)
    {
        position += 1;
    }
    else if (state == 2 || state == 4 || state == 11 || state == 13)
    {
        position -= 1;
    }
    else if(state == 3 || state == 12)
    {
        position += 2;
    }
    else if(state == 6 || state == 9)
    {
        position -= 2;
    }
}

int Encoder::read()
{
    return position;
}
