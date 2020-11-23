#include "robot.h"
#include "../odometry/odometry.h"
#include "../math/mathUtil.h"
#include "../math/vector.h"
#include "../BETA/encoderL.h"
#include "../BETA/encoderR.h"
#include <cmath>
#include <ctime>
#include <iostream>

int EncoderL::position = 0;
unsigned char EncoderL::state = 0;

int EncoderR::position = 0;
unsigned char EncoderR::state = 0;

Robot::Robot(int lMotorDirPin, int lMotorPowerPin, int rMotorDirPin, int rMotorPowerPin, double initialX, double initialY, double initialTheta)
    : l{lMotorDirPin, lMotorPowerPin}, r{rMotorDirPin, rMotorPowerPin} //initialize motors
{
    setPose(initialX, initialY, initialTheta);

    EncoderL::begin();
    EncoderR::begin();
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
    double initialHeadingRad = toRadians(getHeading() + 90); //add 90 because we want the right to be 0 but right now up is 0

    //flipped because if you actually draw the triangle it works out
    double additionalX = inches * cos(initialHeadingRad);
    double additionalY = inches * sin(initialHeadingRad);

    double finalX = initialX + additionalX;
    double finalY = initialY + additionalY;

    double xError = abs(getX() - finalX);
    double yError = abs(getY() - finalY);
    double error = hypot(xError, yError);
    double pastError = inches;

    double integral = 0;
    double initialAngle = getHeading();

    while (error > 2)
    {
        std::cout << "Left read: " << EncoderL::read() << " Right read: " << EncoderR::read();
        updatePos(EncoderL::read(), EncoderR::read());
        double xError = abs(getX() - finalX);
        double yError = abs(getY() - finalY);
        double error = hypot(xError, yError);
        std::cout << "  X: " << getX();
        std::cout << "  Y: " << getY();
        std::cout << "  error: " << error;

        currentTime = ((std::clock() - timer) / (double)CLOCKS_PER_SEC);
        double dt = currentTime - pastTime;

        double proportional = error / inches;
        integral += dt * ((error + pastError) / 2.0);
        double derivative = (error - pastError) / dt;

        double power = kp * proportional + ki * integral + kd * derivative;
        double angle = getHeading();

        if (power > 0)
        {
            if (abs(angle - initialAngle) > 2)
            {
                if (angleDiff(angle, initialAngle) < 0) //we are too far to the left
                {
                    setMotorPowers(power + f, (power + f) * .8);
                }
                else
                {
                    setMotorPowers((power + f) * .8, power + f);
                }
            }
            else
            {
                setMotorPowers(power + f, power + f);
            }
        }
        else
        {
            if (abs(angle - initialAngle) > 2)
            {
                if (angleDiff(angle, initialAngle) < 0) //we are too far to the left
                {
                    setMotorPowers(power - f, (power - f) * .8);
                }
                else
                {
                    setMotorPowers((power - f) * .8, power - f);
                }
            }
            else
            {
                setMotorPowers(power - f, power - f);
            }
        }
    }
    setMotorPowers(0, 0);
}

void Robot::setMotorPowers(double lPower, double rPower)
{
    l.setPower(lPower);
    r.setPower(rPower);
    std::cout << "lPower: " << lPower << "  rPower: " << rPower << "\n";
}
