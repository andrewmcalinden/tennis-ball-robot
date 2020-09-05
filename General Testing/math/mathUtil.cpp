#include "mathUtil.h"
#include <cmath>

double angleWrapDeg(double angle)
{
    double correctAngle = angle;
    if (correctAngle > 180)
    {
        correctAngle -= 360;
    }
    else if (correctAngle < -180)
    {
        correctAngle += 360;
    }
    return correctAngle;
}

double angleWrapRad(double angle)
{
    double correctAngle = angle;
    if (correctAngle > M_PI)
    {
        correctAngle -= (2 * M_PI);
    }
    else if (correctAngle < (-1 * M_PI))
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