#include "robot.h"
#include "../odometry/odometry.h"
#include "../math/mathUtil.h"
#include "../math/vector.h"
#include <cmath>
#include <ctime>
#include <iostream>

Robot::Robot(int lMotorDirPin, int lMotorPowerPin, int rMotorDirPin, int rMotorPowerPin,
             double initialX, double initialY, double initialTheta,
             int lEncoderPin1, int lEncoderPin2, int rEncoderPin1, int rEncoderPin2)
    : l{lMotorDirPin, lMotorPowerPin}, r{rMotorDirPin, rMotorPowerPin}, encoderL{lEncoderPin1, lEncoderPin2}, encoderR{rEncoderPin1, rEncoderPin2} //initialize motors and encoders
{
    setPose(initialX, initialY, initialTheta);
}

void Robot::goStraight(double inches, double kp, double ki, double kd, double f)
{
    std::clock_t timer;
    timer = std::clock();

    double pastTime = 0;
    double currentTime = ((std::clock() - timer) / (double)CLOCKS_PER_SEC);

    double initialX = getX();
    double initialY = getY();
    double initialHeadingRad = toRadians(getHeading() + 90); //add 90 because we want the right to be 0 but right now up is 0

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

    while (abs(error) > 2)
    {
        updatePos(encoderL.read(), encoderR.read());
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
        std::cout << "  power: " << power << "\n"; 
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