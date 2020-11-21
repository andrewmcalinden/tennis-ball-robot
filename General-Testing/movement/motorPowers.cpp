#include "motorPowers.h"

MotorPowers::MotorPowers(double wantedLPower, double wantedRPower)
{
    lPower = wantedLPower;
    rPower = wantedRPower;
}

void MotorPowers::setLPower(double power)
{
    lPower = power;
}

void MotorPowers::setRPower(double power)
{
    rPower = power;
}

double MotorPowers::getLPower()
{
    return lPower;
}

double MotorPowers::getRPower()
{
    return rPower;
}