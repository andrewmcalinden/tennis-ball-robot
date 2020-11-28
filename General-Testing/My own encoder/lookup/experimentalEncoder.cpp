#include "experimentalEncoder.h"
#include <wiringPi.h>
#include <vector>
#include <iostream>

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

static std::vector<ExperimentalEncoder*> lookupTable;

void update(unsigned char pin)
{
    for (int i = 0; i < lookupTable.size(); i++)
    {
        if (lookupTable.at(i)->pinA == pin || lookupTable.at(i)->pinB == pin) //found the encoder which is interrupting
        {
            ExperimentalEncoder *currentEncoder = lookupTable.at(i);

            unsigned char currentState = (currentEncoder->state) & 3;

            std::cout << "readA: " << digitalRead(currentEncoder->pinA) << "readB: " << digitalRead(currentEncoder->pinB) << "\n";
            if (digitalRead(currentEncoder->pinA))
            {
                currentState |= 4;
            }
            if (digitalRead(currentEncoder->pinB))
            {
                currentState |= 8;
            }

            (currentEncoder->state) = currentState >> 2;

            //std::cout << "current state: " << static_cast<unsigned>(currentState) << std::endl;

            if (currentState == 1 || currentState == 7 || currentState == 8 || currentState == 14)
            {
                (currentEncoder->position) += 1;
            }
            else if (currentState == 2 || currentState == 4 || currentState == 11 || currentState == 13)
            {
                (currentEncoder->position) -= 1;
            }
            else if (currentState == 3 || currentState == 12)
            {
                (currentEncoder->position) += 2;
            }
            else if (currentState == 6 || currentState == 9)
            {
                (currentEncoder->position) -= 2;
            }
        }
    }
}

void interrupt0(void) { update(0); }
void interrupt2(void) { update(2); }
void interrupt3(void) { update(3); }
void interrupt7(void) { update(7); }

void ExperimentalEncoder::registerCallback()
{
    lookupTable.push_back(this);
    switch (pinA)
    {
    case 0:
        wiringPiISR(0, INT_EDGE_BOTH, &interrupt0);
        break;
    case 2:
        wiringPiISR(2, INT_EDGE_BOTH, &interrupt2);
        break;
    case 3:
        wiringPiISR(3, INT_EDGE_BOTH, &interrupt3);
        break;
    case 7:
        wiringPiISR(7, INT_EDGE_BOTH, &interrupt7);
        break;
    }
    switch (pinB)
    {
    case 0:
        wiringPiISR(0, INT_EDGE_BOTH, &interrupt0);
        break;
    case 2:
        wiringPiISR(2, INT_EDGE_BOTH, &interrupt2);
        break;
    case 3:
        wiringPiISR(3, INT_EDGE_BOTH, &interrupt3);
        break;
    case 7:
        wiringPiISR(7, INT_EDGE_BOTH, &interrupt7);
        break;
    }
}

int ExperimentalEncoder::read()
{
    return position;
}