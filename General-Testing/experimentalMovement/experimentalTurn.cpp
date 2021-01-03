#include "experimentalTurn.h"
#include "../math/mathUtil.h"
#include <iostream>
ExperimentalTurn::ExperimentalTurn(double endHeading, double p, double i, double d, double specificF)
{
    finalHeading = endHeading;

    kp = p;
    ki = i;
    kd = d;
    f = specificF;

    done = false;
}

void ExperimentalTurn::updatePower(pose currentPose)
{
    error = -angleDiff(currentPose.heading, finalHeading);
    std::cout << "  error: " << error;

    currentTime = ((std::clock() - timer) / (double)CLOCKS_PER_SEC);
    double dt = currentTime - pastTime;

    double proportional = error / initialAngleDiff;
    std::cout << "  p: " << proportional << "\n";
    integral += dt * ((error + pastError) / 2.0);
    std::cout << "  i: " << integral << "\n";
    double derivative = (error - pastError) / dt;
    std::cout << "  d: " << derivative << "\n";

    double power = kp * proportional + ki * integral + kd * derivative;
    std::cout << "  power: " << power << "\n";

    if (power > 0)
    {
        leftPower = power + f;
        rightPower = -power - f;
    }
    else
    {
        leftPower = -power - f;
        rightPower = power + f;
    }
    pastTime = currentTime;
    pastError = error;

    if (abs(error) < 2)
    {
        done = true;
    }
}

void ExperimentalTurn::beginMovement(pose startPose)
{
    initialHeading = startPose.heading;
    initialAngleDiff = initialHeading - finalHeading;

    error = angleDiff(startPose.heading, initialHeading);
    pastError = error;

    integral = 0;

    timer = std::clock();
    pastTime = 0;
    currentTime = ((std::clock() - timer) / (double)CLOCKS_PER_SEC);
}