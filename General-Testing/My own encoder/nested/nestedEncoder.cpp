#include "nestedEncoder.h"
#include <wiringPi.h>
NestedEncoder::NestedEncoder(int pinALoc, int pinBLoc)
    : pinA{pinALoc}, pinB{pinBLoc}
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
    registerCallback();
}

// void NestedEncoder::EncoderReference::setCallBackObject()
// {
//     callbackObject = this;
// }

NestedEncoder *NestedEncoder::EncoderReference::callbackObject = this;

void NestedEncoder::callbackMethod()
{
    EncoderReference::callbackObject->update();
}

void NestedEncoder::registerCallback()
{
    wiringPiISR(pinA, INT_EDGE_BOTH, &NestedEncoder::callbackMethod);
    wiringPiISR(pinB, INT_EDGE_BOTH, &NestedEncoder::callbackMethod);
}

void NestedEncoder::update()
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

int NestedEncoder::read()
{
    return position;
}