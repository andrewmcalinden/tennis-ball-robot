#include <cmath>
#include <iostream>

#include "odometry.h"
#include "vector.h"
#include "mathUtil.h"

#define TRACKWIDTH 16
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

//might want to make current tics a parameter in updatePos
void updateLeftEncoder(double reading)
{
    double currentInches = reading; //actual encoder reading
    leftChange = currentInches - prevLeft;
    prevLeft = currentInches;
}

void updateRightEncoder(double reading)
{
    double currentInches = reading; //actual encoder reading
    rightChange = currentInches - prevRight;
    prevRight = currentInches;
}

void updatePos(double leftReading, double rightReading)
{
    //find left and right change
    updateLeftEncoder(leftReading);
    updateRightEncoder(rightReading);

    //store initialHeading for later
    double initialHeading = globalHeading;
    double initialHeadingRad = (initialHeading * M_PI) / 180.0;

    double angleChangeRad = (leftChange - rightChange) / TRACKWIDTH;
    double angleChangeDeg = (180 * angleChangeRad) / M_PI;
    globalHeading = angleWrapDeg(globalHeading + angleChangeDeg);

    double movement = (leftChange + rightChange) / 2.0; // total change in movement by robot (dx)
    double dTheta = angleChangeRad;

    std::cout << movement << " " << dTheta << "\n";

    double sinTheta = sin(dTheta);
    double cosTheta = cos(dTheta);

    double sineTerm;
    double cosTerm;

    //if we have almost no angle change
    if (epsilonEquals(dTheta, 0))
    {
        sineTerm = 1.0 - 1.0 / 6.0 * dTheta * dTheta;
        cosTerm = dTheta / 2.0;
    }
    else //we have angle change
    {
        sineTerm = sinTheta / dTheta;
        cosTerm = (1 - cosTheta) / dTheta;
    }

    Vector deltaVector = Vector(sineTerm * movement, cosTerm * movement); //translation

    deltaVector = deltaVector.rotated(initialHeadingRad);

    //switch x, y because thats the only way it works idk lol
    globalXPos += deltaVector.getY();
    globalYPos += deltaVector.getX();
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
