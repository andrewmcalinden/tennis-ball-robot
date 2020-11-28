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