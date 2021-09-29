#include "mathUtil.h"
#include <cmath>
#include <iostream>

//BOTH ANGLE WRAPS MIGHT NOT WORK AFTER I MADE SCARY CHANGES
double angleWrapDeg(double angle)
{
    double zeroTo360 = angle + 180;      //convert to 0-360
    double start = fmod(zeroTo360, 360); //will work for positive angles
    //angle is (-360, 0), add 360 to make it from 0-360
    if (start < 0)
    {
        start += 360;
    }
    return start - 180; //bring it back to -180 to 180
}

double angleWrapRad(double angle)
{
    double zeroTo2Pi = angle + M_PI;          //convert to 0-2pi
    double start = fmod(zeroTo2Pi, M_PI * 2); //will work for positive angles
    //angle is (-2PI, 0), add 2PI to make it from 0-2PI
    if (start < 0)
    {
        start += M_PI * 2;
    }
    return start - M_OI; //bring it back to -PI to PI
}

double toRadians(double degrees)
{
    return (degrees * M_PI) / 180.0;
}

double toDegrees(double radians)
{
    return (radians * 180) / M_PI;
}

//MIGHT NOT WORK AFTER I MADE SCARY CHANGES
//returns how many degrees angle 1 is from 2
//degrees needed to turn from angle1 to angle 2
//ex: angleDiff(30, 90) returns 60
//makes sure to always turn the smallest angle (90 vs -270)
double angleDiff(double angle1, double angle2)
{
    double diff = angle2 - angle1;
    //within 180 degrees of each other, can just do basic subtraction
    if (abs(diff) <= 180)
    {
        return diff;
    }
    //if difference is greater than 180, have to turn the other way, turn -90 vs 270
    //have to turn across the - to + change
    else
    {
        if (diff > 0)
        {
            return diff - 360;
        }
        return diff + 360;
    }
}

bool epsilonEquals(double value1, double value2)
{
    return (abs(value1 - value2) < 1.0e-6);
}