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
    wiringPiISR(pinA, INT_EDGE_BOTH, &Encoder::updateCallback, this);
    wiringPiISR(pinB, INT_EDGE_BOTH, &Encoder::updateCallback, this));
}

void Encoder::update()
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

static void updateCallback(void this_pointer)
{
    Encoder self = static_cast<Encoder>(this_pointer);
    self->update();
}

int Encoder::read()
{
    return position;
}
