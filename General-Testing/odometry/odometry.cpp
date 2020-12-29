#include "odometry.h"
#include "../math/vector.h"
#include "../math/mathUtil.h"
#include <cmath>
#include <iostream>
#include <cstdlib>

#define TRACKWIDTH 16.5
#define PULSES_PER_REV 1440.0
#define EPSILON 1.0e-6
#define LEFT_WHEEL__DIAMETER 2.061
#define RIGHT_WHEEL_DIAMETER 2.032

//defenitions, just like we define functions below
double globalXPos = 0;
double globalYPos = 0;
double globalHeading = 0; //in degrees, from -180 to 180

double prevLeft = 0;
double prevRight = 0;
double leftChange = 0;
double rightChange = 0;

void setPose(double x, double y, double theta)
{
    globalXPos = x;
    globalYPos = y;
    globalHeading = theta;
}

bool epsilonEquals(double value1, double value2)
{
    return (abs(value1 - value2) < EPSILON);
}

void updateLeftEncoder(double reading)
{
    const double currentPulses = reading; //actual encoder reading
    const double currentRotations = currentPulses / PULSES_PER_REV;
    const double currentInches = currentRotations * LEFT_WHEEL__DIAMETER * M_PI;
    leftChange = currentInches - prevLeft;
    prevLeft = currentInches;
}

void updateRightEncoder(double reading)
{
    const double currentPulses = reading; //actual encoder reading
    const double currentRotations = currentPulses / PULSES_PER_REV;
    const double currentInches = currentRotations * RIGHT_WHEEL_DIAMETER * M_PI;
    rightChange = currentInches - prevRight;
    prevRight = currentInches;
}

void updatePos(double leftReading, double rightReading)
{
    //find left and right change
    updateLeftEncoder(leftReading);
    updateRightEncoder(rightReading);

    //store initialHeading for later
    const double initialHeading = globalHeading;
    const double initialHeadingRad = toRadians(initialHeading);

    const double angleChangeRad = (rightChange - leftChange) / TRACKWIDTH;
    const double angleChangeDeg = toDegrees(angleChangeRad);
    globalHeading = angleWrapDeg(globalHeading + angleChangeDeg);

    const double movement = (leftChange + rightChange) / 2.0; // total change in movement by robot (dx)
    const double dTheta = angleChangeRad;

    const double sinTheta = sin(dTheta);
    const double cosTheta = cos(dTheta);

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

    //switch x, y because thats then +y is forward
    //-y because then +x is forwards
    globalXPos += deltaVector.getY();
    globalYPos -= deltaVector.getX();
}