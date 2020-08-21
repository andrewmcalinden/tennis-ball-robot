#include <cmath>
#include <iostream>

#include "Odometry.h"
#include "Vector.h"

#define TRACKWIDTH 1
#define EPSILON 1.0e-6

double globalXPos = 0;
double globalYPos = 0;
double globalHeading = 0; //in degrees, from -180 to 180


double prevLeft = 0;
double prevRight = 0;
double leftChange = 0;
double rightChange = 0;

bool epsilonEquals(double value1, double value2)
{
    return (abs(value1 - value2) < EPSILON);
}

void updateLeftEncoder()
{
    double currentInches = 0; //actual current inches
    leftChange = currentInches - prevLeft;
    prevLeft = currentInches;
}

void updateRightEncoder()
{
    double currentInches = 0; //actual current inches
    rightChange = currentInches - prevRight;
    prevRight = currentInches;
}

void updatePos()
{
    //find left and right change
    updateLeftEncoder();
    updateRightEncoder();

    double angleChangeRad = (leftChange + rightChange) / TRACKWIDTH;
    double angleChangeDeg = (180 * angleChangeRad) / M_PI;
    globalHeading = angleWrap(globalHeading + angleChangeDeg);

    double movement = (leftChange + rightChange) / 2.0; // total change in movement by robot
    double dTheta = angleChangeRad;
    double sineTerm;
    double cosTerm;

    //if we have almost no angle change
    if (epsilonEquals(dTheta, 0))
    {
        sineTerm = 1.0 - dTheta * dTheta / 6.0;
        cosTerm = dTheta / 2.0;
    }
    else //we have angle change
    {
        sineTerm = sin(dTheta) / dTheta;
        cosTerm = (1 - cos(dTheta)) / dTheta;
    }

    Vector deltaVector = Vector(cosTerm * movement, sineTerm * movement);
    deltaVector = deltaVector.rotated(globalHeading);

    globalXPos += deltaVector.getX();
    globalYPos += deltaVector.getY();
}

double angleWrap(double angle)
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

double getX()
{
    return globalXPos;
}

double getY()
{
    return globalYPos;
}

double getHeading()
{
    return globalHeading;
}
