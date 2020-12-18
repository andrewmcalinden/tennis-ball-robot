#include "experimentalLine.h"
#include "../math/pose.h"
#include "../math/mathUtil.h"
#include <cmath>
ExperimentalLine::ExperimentalLine(pose endPose, double p, double i, double d, double specificF)
{
    finalPose = endPose;

    kp = p;
    ki = i;
    kd = d;
    f = specificF;

    done = false;
}

void ExperimentalLine::beginMovement(pose startPose)
{
    double initialX = startPose.x;
    double initialY = startPose.y;
    double initialHeadingRad = toRadians(startPose.heading + 90); //add 90 because we want the right to be 0 but right now up is 0

    initialDistance = hypot(abs(initialX - finalPose.x), abs(initialY - finalPose.y));

    double additionalX = initialDistance * cos(initialHeadingRad);
    double additionalY = initialDistance * sin(initialHeadingRad);

    double finalX = initialX + additionalX;
    double finalY = initialY + additionalY;

    double error = initialDistance;
    double pastError = error;

    integral = 0;
    initialHeading = startPose.heading;

    timer = std::clock();
    pastTime = 0;
    currentTime = ((std::clock() - timer) / (double)CLOCKS_PER_SEC);
}