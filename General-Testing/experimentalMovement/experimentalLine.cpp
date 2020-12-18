#include "experimentalLine.h"
#include "../math/mathUtil.h"
#include <cmath>
#include <iostream>
ExperimentalLine::ExperimentalLine(double distance, double p, double i, double d, double specificF)
{
    initialDistance = distance;

    kp = p;
    ki = i;
    kd = d;
    f = specificF;

    done = false;
}

void ExperimentalLine::beginMovement(pose startPose)
{
    initialPose.x = startPose.x;
    initialPose.y = startPose.y;
    double initialHeadingRad = toRadians(startPose.heading + 90); //add 90 because we want the right to be 0 but right now up is 0

    double additionalX = initialDistance * cos(initialHeadingRad);
    double additionalY = initialDistance * sin(initialHeadingRad);

    finalPose.x = initialPose.x + additionalX;
    finalPose.y = initialPose.y + additionalY;
    finalPose.heading = startPose.heading;

    error = initialDistance;
    pastError = error;

    integral = 0;
    initialPose.heading = startPose.heading;

    timer = std::clock();
    pastTime = 0;
    currentTime = ((std::clock() - timer) / (double)CLOCKS_PER_SEC);
}

void ExperimentalLine::updatePower(pose currentPose)
{
    double xError = abs(currentPose.x - finalPose.x);
    double yError = abs(currentPose.y - finalPose.y);
    error = hypot(xError, yError);
    std::cout << "  error: " << error;

    currentTime = ((std::clock() - timer) / (double)CLOCKS_PER_SEC);
    double dt = currentTime - pastTime;

    double proportional = error / initialDistance;
    integral += dt * ((error + pastError) / 2.0);
    double derivative = (error - pastError) / dt;

    double power = kp * proportional + ki * integral + kd * derivative;
    std::cout << "  power: " << power << "\n";
    double angle = currentPose.heading;

    if (power > 0)
    {
        if (abs(angle - initialPose.heading) > 2)
        {
            if (angleDiff(angle, initialPose.heading) < 0) //we are too far to the left
            {
                leftPower = power + f;
                rightPower = (power + f) * .8;
            }
            else
            {
                leftPower = (power + f) * .8;
                rightPower = power + f;
            }
        }
        else
        {
            leftPower = power + f;
            rightPower = power + f;
        }
    }
    else
    {
        if (abs(angle - initialPose.heading) > 2)
        {
            if (angleDiff(angle, initialPose.heading) < 0) //we are too far to the left
            {
                leftPower = power - f;
                rightPower = (power - f) * .8;
            }
            else
            {
                leftPower = (power - f) * .8;
                rightPower = power - f;
            }
        }
        else
        {
            leftPower = power - f;
            rightPower = power - f;
        }
    }
    pastTime = currentTime;
    pastError = error;
}