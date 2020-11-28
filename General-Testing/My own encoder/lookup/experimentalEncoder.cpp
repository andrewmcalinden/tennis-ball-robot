#include "experimentalEncoder.h"
#include <wiringPi.h>
#include <vector>

void Interrupt0 (void){digitalWrite(3, HIGH);}
ExperimentalEncoder::ExperimentalEncoder(int pinALoc, int pinBLoc)
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

static ExperimentalEncoder* callbackObject;
static std::vector<ExperimentalEncoder*> lookupTable;

void ExperimentalEncoder::callbackMethod()
{
    ExperimentalEncoder* currentCallbackObject = lookupTable.at(location); //this is the only error
    currentCallbackObject->update();
}

void ExperimentalEncoder::registerCallback()
{
    callbackObject = this;
    lookupTable.push_back(callbackObject);
    location = lookupTable.size() - 1;
    wiringPiISR(pinA, INT_EDGE_BOTH, &ExperimentalEncoder::callbackMethod);
    wiringPiISR(pinB, INT_EDGE_BOTH, &ExperimentalEncoder::callbackMethod);
}

void ExperimentalEncoder::update()
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

int ExperimentalEncoder::read()
{
    return position;
}
