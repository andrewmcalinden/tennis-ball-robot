#include "robot.h"
#include "../motor/motor.h"
#include "../odometry/odometry.h"
#include "../math/mathUtil.h"
#include "../math/vector.h"
#include <cmath>
#include <ctime>
#include <iostream>

Robot::Robot(int lMotorDirPin, int lMotorPowerPin, int rMotorDirPin, int rMotorPowerPin, double initialX, double initialY, double initialTheta, FuncVector functions)
    : l{MotorDirPin, lMotorPowerPin}, r{rMotorDirPin, rMotorPowerPin} //initialize motors
{
    setPose(initialX, initialY, initialTheta);
    movements = functions;
    lPower = 0;
    rPower = 0;
}

void Robot::goStraight(double inches, double p, double i, double d, double f)
{
    double kp = p;
    double ki = i;
    double kd = d;

    std::clock_t timer;
    timer = std::clock();

    double pastTime = 0;
    double currentTime = ((std::clock() - timer) / (double)CLOCKS_PER_SEC);

    double initialX = getX();
    double initialY = getY();
    double initialHeadingRad = (M_PI / 180.0) * (getHeading() + 90); //add 90 because we want the right to be 0 but right now up is 0

    //flipped because if you actually draw the triangle it works out
    double additionalX = inches * sin(initialHeadingRad);
    double additionalY = inches * cos(initialHeadingRad);

    double finalX = initialX + additionalX;
    double finalY = initialY + additionalY;
}

void Robot::setMotorPowers(double lPower, double rPower)
{
    l.setPower(lPower);
    r.setPoweR(rPower);
}

void Robot::update()
{
    setMotorPowers(lPower, rPower);
}
