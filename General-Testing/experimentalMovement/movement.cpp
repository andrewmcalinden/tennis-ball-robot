#include "movement.h"
motorPowers Movement::getPowers()
{
    return motorPowers{leftPower, rightPower};
}

bool Movement::finished()
{
    return done;
}

