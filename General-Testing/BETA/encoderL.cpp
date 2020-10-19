#include "encoderL.h"
EncoderL::EncoderL()
{
    EncoderL::pinA = 2;
    EncoderL::pinB = 3;
    EncoderL::position = 0;
    EncoderL::state = 0;

    wiringPiSetup();
    pinMode(EncoderL::pinA, INPUT);
    pinMode(EncoderL::pinB, INPUT);

    if (digitalRead(EncoderL::pinA))
    {
        EncoderL::state |= 1;
    }
    if (digitalRead(EncoderL::pinB))
    {
        EncoderL::state |= 2;
    }

    wiringPiISR(pinA, INT_EDGE_BOTH, &update);
    wiringPiISR(pinB, INT_EDGE_BOTH, &update);
}

void EncoderL::update()
{
    unsigned char currentState = EncoderL::state & 3;
    if (digitalRead(EncoderL::pinA))
    {
        currentState |= 4;
    }
    if (digitalRead(EncoderL::pinB))
    {
        currentState |= 8;
    }

    EncoderL::state = currentState >> 2;

    if (currentState == 1 || currentState == 7 || currentState == 8 || currentState == 14)
    {
        EncoderL::position += 1;
    }
    else if (currentState == 2 || currentState == 4 || currentState == 11 || currentState == 13)
    {
        EncoderL::position -= 1;
    }
    else if (currentState == 3 || currentState == 12)
    {
        EncoderL::position += 2;
    }
    else if (currentState == 6 || currentState == 9)
    {
        EncoderL::position -= 2;
    }
}

int EncoderL::read()
{
    return EncoderL::position;
}