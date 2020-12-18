#include "movement.h"
motorPowers Movement::getPowers()
{
    motorPowers m;
    m.lPower = leftPower;
    m.rPower = rightPower;
    return m;
}

bool Movement::finished()
{
    return done;
}

