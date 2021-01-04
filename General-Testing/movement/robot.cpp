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

//note: negative power moves forwards
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

    double firstTimeAtSetpoint = 0;
    double timeAtSetPoint = 0;
    bool atSetpoint = false;

    while (timeAtSetPoint < .1)
    {
        updatePos(encoderL.read(), encoderR.read());
        const double xError = abs(globalXPos - finalX);
        const double yError = abs(globalYPos - finalY);
        error = hypot(xError, yError);
        printf("X: %.2f", globalXPos);
        printf("\tY: %.2f", globalYPos);
        printf("\terror: %.2f\n", error);

        currentTime = ((std::clock() - timer) / (double)CLOCKS_PER_SEC);
        const double dt = currentTime - pastTime;

        const double proportional = error / inches;
        integral += dt * ((error + pastError) / 2.0);
        const double derivative = (error - pastError) / dt;

        const double power = kp * proportional + ki * integral + kd * derivative;
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

        if (fabs(error) < .5)
        {
            if(!atSetpoint)
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
    }
    std::cout << "\nWE ARE STOPPING MOTORS!!!!!!!!!!!!!!!!!!" << std::endl << "abs error: " << fabs(error) << std::endl;
    setMotorPowers(0, 0);
}

void Robot::turnHeading(double finalAngle, double kp, double ki, double kd, double f)
{
    std::ofstream outputFile("pidData.txt");

    std::clock_t timer;
    timer = std::clock();

    double pastTime = 0;
    double currentTime = ((std::clock() - timer) / (double)CLOCKS_PER_SEC);

    const double initialHeading = globalHeading;

    finalAngle = angleWrapDeg(finalAngle);

    const double initialAngleDiff = initialHeading - finalAngle;
    double error = angleDiff(globalHeading, finalAngle);
    double pastError = error;

    double firstTimeAtSetpoint = 0;
    double timeAtSetPoint = 0;
    bool atSetpoint = false;

    double integral = 0;

    while (timeAtSetPoint < .05)
    {
        updatePos(encoderL.read(), encoderR.read());
        error = angleDiff(globalHeading, finalAngle);
        //printf( "\rglobalHeading: %.2f", globalHeading);
        //printf("\tfinalAngle: %.2f", finalAngle);
        printf( "\rerror: %.2f", error);

        currentTime = ((std::clock() - timer) / (double)CLOCKS_PER_SEC);
        const double dt = currentTime - pastTime;
        std::cout << "\tdt: " << std::scientific << dt; 

        //we negate error because 
        const double proportional = error / abs(initialAngleDiff);
        integral += dt * ((error + pastError) / 2.0);
        const double derivative = (error - pastError) / dt;
        printf("\terror change: %.2f", error - pastError);
        printf("\td: %.3f", derivative * kd);
        outputFile << derivative * kd << "\n";


        const double power = kp * proportional + ki * integral + kd * derivative;
        if (power > 0)
        {
            setMotorPowers(-power - f, power + f);

        }
        else
        {
            setMotorPowers(-power + f, power - f);
        }

        if (fabs(error) < .5)
        {
            if(!atSetpoint)
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
    }
    std::cout << "\nWE ARE STOPPING MOTORS!!!!!!!!!!!!!!!!!!" << std::endl << "abs error: " << fabs(error) << std::endl;
    setMotorPowers(0, 0);
}

void Robot::setMotorPowers(double lPower, double rPower)
{
    l.setPower(lPower);
    r.setPower(rPower);
    printf( "lPower: %.3f", lPower);
    printf("\trPower: %.3f\t", rPower);
}