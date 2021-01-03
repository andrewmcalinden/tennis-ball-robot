#include "robot.h"
#include "../odometry/odometry.h"
#include "../math/mathUtil.h"
#include "../math/vector.h"
#include <cmath>
#include <ctime>
#include <iostream>

Robot::Robot(unsigned char lMotorDirPin, unsigned char lMotorPowerPin, unsigned char rMotorDirPin, unsigned char rMotorPowerPin,
             double initialX, double initialY, double initialTheta,
             unsigned char lEncoderPin1, unsigned char lEncoderPin2, unsigned char rEncoderPin1, unsigned char rEncoderPin2)
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

    const double initialX = globalXPos;
    const double initialY = globalYPos;
    const double initialHeadingRad = toRadians(globalHeading + 90); //add 90 because we want the right to be 0 but right now up is 0

    const double additionalX = inches * cos(initialHeadingRad);
    const double additionalY = inches * sin(initialHeadingRad);

    const double finalX = initialX + additionalX;
    const double finalY = initialY + additionalY;

    double error = inches;
    double pastError = error;

    double integral = 0;
    const double initialAngle = globalHeading;

    while (abs(error) > 2)
    {
        updatePos(encoderL.read(), encoderR.read());
        const double xError = abs(globalXPos - finalX);
        const double yError = abs(globalYPos - finalY);
        error = hypot(xError, yError);
        std::cout << "  X: " << globalXPos;
        std::cout << "  Y: " << globalYPos;
        std::cout << "  error: " << error;

        currentTime = ((std::clock() - timer) / (double)CLOCKS_PER_SEC);
        const double dt = currentTime - pastTime;

        const double proportional = error / inches;
        integral += dt * ((error + pastError) / 2.0);
        const double derivative = (error - pastError) / dt;

        const double power = kp * proportional + ki * integral + kd * derivative;
        std::cout << "  power: " << power << "\n";
        const double angle = globalHeading;

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
        pastTime = currentTime;
        pastError = error;
     }
    setMotorPowers(0, 0);
}

void Robot::turnHeading(double finalAngle, double kp, double ki, double kd, double f)
{
    std::clock_t timer;
    timer = std::clock();

    double pastTime = 0;
    double currentTime = ((std::clock() - timer) / (double)CLOCKS_PER_SEC);

    const double initialHeading = globalHeading;

    const double initialAngleDiff = initialHeading - finalAngle;
    double error = angleDiff(globalHeading, finalAngle);
    double pastError = error;

    double integral = 0;

    while (abs(error) > 2)
    {
        updatePos(encoderL.read(), encoderR.read());
        error = angleDiff(globalHeading, finalAngle);
        printf( "\rglobalHeading: %.2f", globalHeading);
        printf("\tfinalAngle: %.2f", finalAngle);
        printf( "error: %.2f", error);

        currentTime = ((std::clock() - timer) / (double)CLOCKS_PER_SEC);
        const double dt = currentTime - pastTime;

        const double proportional = error / initialAngleDiff;
        integral += dt * ((error + pastError) / 2.0);
        const double derivative = (error - pastError) / dt;

        const double power = kp * proportional + ki * integral + kd * derivative;
        if (power > 0)
        {
            setMotorPowers(power + f, -power - f);

        }
        else
        {
            setMotorPowers(-power - f, power + f);
        }
        pastTime = currentTime;
        pastError = error;
    }
    setMotorPowers(0, 0);
}

void Robot::setMotorPowers(double lPower, double rPower)
{
    l.setPower(lPower);
    r.setPower(rPower);
    printf( "\t left: %.3f", lPower);
    printf("\tright: %.3f", rPower);
}