#include "robot.h"
#include "../odometry/odometry.h"
#include "../math/mathUtil.h"
#include "../math/vector.h"
#include <wiringPi.h>
#include <cmath>
#include <ctime>
#include <iostream>
#include <fstream>

Robot::Robot(unsigned char lMotorDirPin, unsigned char lMotorPowerPin, unsigned char rMotorDirPin, unsigned char rMotorPowerPin,
             double initialX, double initialY, double initialTheta,
             unsigned char lEncoderPin1, unsigned char lEncoderPin2, unsigned char rEncoderPin1, unsigned char rEncoderPin2)
    : l{lMotorDirPin, lMotorPowerPin}, r{rMotorDirPin, rMotorPowerPin}, encoderL{lEncoderPin1, lEncoderPin2}, encoderR{rEncoderPin1, rEncoderPin2} //initialize motors and encoders
{
    setPose(initialX, initialY, initialTheta);
}

void Robot::goStraight(double inches, double kp, double ki, double kd, double f)
{
    std::ofstream outputFile("straightData.txt");

    std::clock_t timer;
    timer = std::clock();

    double pastTime = 0;
    double currentTime = ((std::clock() - timer) / (double)CLOCKS_PER_SEC);

    double initialX = getX();
    double initialY = getY();

    const double initialHeadingRad = toRadians(getHeading() + 90); //add 90 because we want the right to be 0 but right now up is -90

    double additionalX = inches * cos(initialHeadingRad);
    double additionalY = inches * sin(initialHeadingRad);

    const double finalX = initialX + additionalX;
    const double finalY = initialY + additionalY;

    double error = inches;
    double pastError = error;

    double integral = 0;
    const double initialAngle = getHeading();

    double firstTimeAtSetpoint = 0;
    double timeAtSetPoint = 0;
    bool atSetpoint = false;

    while (timeAtSetPoint < .3)
    {
        updatePos(encoderL.read(), encoderR.read());
        double xError = finalX - getX();
        double yError = finalY - getY();

        double direction = angleWrapDeg(toDegrees(atan2(yError, xError)) - getHeading()); //if 90, forward, if -90, backward

        error = hypot(xError, yError); //really abs(error)

        currentTime = ((std::clock() - timer) / (double)CLOCKS_PER_SEC);
        double dt = currentTime - pastTime;

        double proportional = error / fabs(inches);
        integral += dt * ((error + pastError) / 2.0);
        double derivative = (error - pastError) / dt;

        outputFile << "Error: " << error << "\tP: " << proportional * kp << "\tI: " << integral * ki << "\tD: " << derivative * kd << std::endl;
        std::cout << "\r" << error;

        //power will always be positive due to hypot always being positive
        double power = kp * proportional + ki * integral + kd * derivative;
        double angle = getHeading();

        if (direction > 0 && direction < 180) //90 is perfectly forwards
        {
            if (fabs(angle - initialAngle) > .25)
            {
                if (angleDiff(angle, initialAngle) < 0) //we are too far to the left
                {
                    setMotorPowers(power + f, (power + f) * .7);
                }
                else
                {
                    setMotorPowers((power + f) * .7, power + f);
                }
            }
            else
            {
                setMotorPowers(power + f, power + f);
            }
        }
        else //direction = -90
        {
            if (fabs(angle - initialAngle) > .25)
            {
                if (angleDiff(angle, initialAngle) < 0) //we are too far to the left
                {
                    setMotorPowers((-power - f) * .7, -power - f);
                }
                else
                {
                    setMotorPowers(-power - f, (-power - f) * .7);
                }
            }
            else
            {
                setMotorPowers(-power - f, -power - f);
            }
        }

        if (fabs(error) < 1)
        {
            if (!atSetpoint)
            {
                atSetpoint = true;
                firstTimeAtSetpoint = currentTime;
            }
            else //at setpoint
            {
                timeAtSetPoint = currentTime - firstTimeAtSetpoint;
            }
        }
        else //no longer at setpoint
        {
            atSetpoint = false;
            timeAtSetPoint = 0;
        }
        pastTime = currentTime;
        pastError = error;
        delay(12);
    }
    std::cout << "\nabs error: " << fabs(error) << std::endl;
    setMotorPowers(0, 0);
}

void Robot::turnHeading(double finalAngle, double kp, double ki, double kd, double f)
{
    std::ofstream outputFile("turnData.txt");

    std::clock_t timer;
    timer = std::clock();

    double pastTime = 0;
    double currentTime = ((std::clock() - timer) / (double)CLOCKS_PER_SEC);

    const double initialHeading = getHeading();
    finalAngle = angleWrapDeg(finalAngle);

    const double initialAngleDiff = initialHeading - finalAngle;
    double error = angleDiff(getHeading(), finalAngle);
    double pastError = error;

    double firstTimeAtSetpoint = 0;
    double timeAtSetPoint = 0;
    bool atSetpoint = false;

    double integral = 0;

    while (timeAtSetPoint < .0025)
    {
        updatePos(encoderL.read(), encoderR.read());
        error = angleDiff(getHeading(), finalAngle);

        currentTime = ((std::clock() - timer) / (double)CLOCKS_PER_SEC);
        double dt = currentTime - pastTime;

        double proportional = error / fabs(initialAngleDiff);
        integral += dt * ((error + pastError) / 2.0);
        double derivative = (error - pastError) / dt;

        double power = kp * proportional + ki * integral + kd * derivative;
        outputFile << "P: " << proportional * kp << "\tI: " << integral * ki << "\tD: " << derivative * kd << "\tpower: " << power << "\n";

        if (power > 0)
        {
            setMotorPowers(-power - f, power + f);
        }
        else
        {
            setMotorPowers(-power + f, power - f);
        }

        if (fabs(error) < 2)
        {
            if (!atSetpoint)
            {
                atSetpoint = true;
                firstTimeAtSetpoint = currentTime;
            }
            else //at setpoint
            {
                timeAtSetPoint = currentTime - firstTimeAtSetpoint;
            }
        }
        else //no longer at setpoint
        {
            atSetpoint = false;
            timeAtSetPoint = 0;
        }

        std::cout << "Error: " << error << "\tTAS: " << timeAtSetPoint << std::endl;

        pastTime = currentTime;
        pastError = error;
        delay(12);
    }
    std::cout << "abs error: " << fabs(error) << std::endl;
    setMotorPowers(0, 0);
}

void Robot::setMotorPowers(double lPower, double rPower)
{
    l.setPower(lPower);
    r.setPower(rPower);
    // printf( "\tlPower: %.3f", lPower);
    // printf("\trPower: %.3f", rPower);
    if (fabs(lPower) > 1 && fabs(rPower) > 1)
    {
        printf("\tTRIED TO SET POWER GREATER THAN 1\n");
    }
}