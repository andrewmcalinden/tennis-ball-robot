#include "mathUtil.h"
#include <cmath>
#include <iostream>

//make while loop for angles like 800 degrees
double angleWrapDeg(double angle)
{
    double correctAngle = angle;
    while (correctAngle > 180)
    {
        correctAngle -= 360;
    }
    while (correctAngle < -180)
    {
        correctAngle += 360;
    }
    return correctAngle;
}

double angleWrapRad(double angle)
{
    double correctAngle = angle;
    while (correctAngle > M_PI)
    {
        correctAngle -= (2 * M_PI);
    }
    while (correctAngle < (-1 * M_PI))
    {
        correctAngle += (2 * M_PI);
    }
    return correctAngle;
}

double toRadians(double degrees)
{
    return (degrees * M_PI) / 180.0;
}

double toDegrees(double radians)
{
    return (radians * 180) / M_PI;
}

//returns how many degrees angle 1 is from 2
//degrees needed to turn from angle1 to angle 2
//ex: angleDiff(30, 90) returns 60
double angleDiff(double angle1, double angle2)
{
    if (angle1 >= 0 && angle2 >= 0 || angle1 <= 0 && angle2 <= 0)
    { //curr & goal are both positive or both negative
        return -(angle1 - angle2);
    }
    else if (abs(angle1 - angle2) <= 180)
    { //diff btwn curr & goal is less than or equal to 180
        return -(angle1 - angle2);
    }
    else if (angle1 > angle2)
    { //curr is greater than goal
        return (360 - (angle1 - angle2));
    }
    else
    { //goal is greater than curr
        return -(360 + (angle1 - angle2));
    }
}

bool epsilonEquals(double value1, double value2)
{
    return (abs(value1 - value2) < 1.0e-6);
}