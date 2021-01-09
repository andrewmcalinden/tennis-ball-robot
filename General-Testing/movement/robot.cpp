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
    std::ofstream outputFile("straightData.txt");

    std::clock_t timer;
    timer = std::clock();

    double pastTime = 0;
    double currentTime = ((std::clock() - timer) / (double)CLOCKS_PER_SEC);

    const double initialX = globalXPos; //0
    const double initialY = globalYPos; //40
    //pi
    const double initialHeadingRad = toRadians(globalHeading + 90); //add 90 because we want the right to be 0 but right now up is -90

    const double additionalX = inches * cos(initialHeadingRad); //-40 
    const double additionalY = inches * sin(initialHeadingRad); //0

    const double finalX = initialX + additionalX; //-40
    const double finalY = initialY + additionalY; // 40

    double error = inches; //40
    double pastError = error; //40

    double integral = 0;
    const double initialAngle = globalHeading; //90

    double firstTimeAtSetpoint = 0;
    double timeAtSetPoint = 0;
    bool atSetpoint = false;

    while (timeAtSetPoint < .3)
    {
        updatePos(encoderL.read(), encoderR.read());
        const double xError = finalX - globalXPos; //-40
        const double yError = finalY - globalYPos; //0

        //90
        double direction = angleWrapDeg(toDegrees(atan2(yError, xError)) - globalHeading); //if 90, forward, if -90, backward
        //printf("\t dir: %.2f", direction);

        //outputFile << "dir: " << direction;

        //40
        error = hypot(xError, yError); //really abs(error)
        // printf("\tX: %.2f", globalXPos);
        // printf("\tY: %.2f", globalYPos);
        printf("\terror: %.2f\n", error);

        //outputFile << "\tX: " << globalXPos << "\tY: " << globalYPos << std::endl;
        
        currentTime = ((std::clock() - timer) / (double)CLOCKS_PER_SEC);
        const double dt = currentTime - pastTime;

        const double proportional = error / abs(inches);
        integral += dt * ((error + pastError) / 2.0);
        const double derivative = (error - pastError) / dt;

        printf("\tp: %.3f", proportional * kp);
        outputFile << "Error: " << error << "\tP: " << proportional * kp << "\tI: " << integral * ki << "\tD: " << derivative * kd << std::endl;
        printf("\ti: %f", integral * ki);
        printf("\td: %.3f", derivative * kd);

        //power will always be positive due to hypot always being positive
        const double power = kp * proportional + ki * integral + kd * derivative;
        const double angle = globalHeading;

        if (direction > 0 && direction < 180) //90 is perfectly forwards
        {
            if (abs(angle - initialAngle) > .25)
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
            if (abs(angle - initialAngle) > .25)
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
    //outputFile << "END OF STRAIGHT" << std::endl;
}

void Robot::turnHeading(double finalAngle, double kp, double ki, double kd, double f)
{
    std::ofstream outputFile("turnData.txt");

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
    double derivative = 0;
    double lastNonZeroD = 0;

    unsigned char cyclesAtSetpoint = 0;

    while (timeAtSetPoint < .025)
    {
        updatePos(encoderL.read(), encoderR.read());
        error = angleDiff(globalHeading, finalAngle);
        printf( "\rerror: %.2f", error);

        currentTime = ((std::clock() - timer) / (double)CLOCKS_PER_SEC);
        const double dt = currentTime - pastTime;
        //std::cout << "\tdt: " << std::scientific << dt; 

        //we negate error because 
        const double proportional = error / abs(initialAngleDiff);
        integral += dt * ((error + pastError) / 2.0);
        derivative = (error - pastError) / dt;
        //printf("\terror change: %.2f", error - pastError);
        printf("\tp: %.3f", proportional * kp);
        printf("\ti: %f", integral * ki);
        printf("\td: %f", derivative * kd);

        //if we have an unusual value of d such as 0 or a very high value, ignore it and use the last normal value
        //if we have a normal value, save it for future reference
        // if(epsilonEquals(derivative, 0) || fabs(derivative * kd) > .3)
        // {
        //     derivative = lastNonZeroD;
        // }
        // else
        // {
        //     lastNonZeroD = derivative;
        // }

        const double power = kp * proportional + ki * integral + kd * derivative;
        outputFile << "P: " << proportional * kp << "\tI: " << integral * ki << "\tD: " << derivative * kd << "\tpower: " << power << "\n";

        if (power > 0)
        {
            setMotorPowers(-power - f, power + f);

        }
        else
        {
            setMotorPowers(-power + f, power - f);
        }

        if (fabs(error) < 1.5)
        {
            // if(!atSetpoint)
            // {
            //     atSetpoint = true;
            //     //firstTimeAtSetpoint = currentTime;
            //     ++cyclesAtSetpoint;
            // }
            // else //at setpoint
            // {
            //     timeAtSetPoint = currentTime - firstTimeAtSetpoint;
            // }
            //atSetpoint = true;
            ++cyclesAtSetpoint;
        }
        else //no longer at setpoint
        {
            //atSetpoint = false;
            // timeAtSetPoint = 0;
            cyclesAtSetpoint = 0;
        }

        pastTime = currentTime;
        pastError = error;
        delay(25);
    }
    std::cout << "\nWE ARE STOPPING MOTORS!!!!!!!!!!!!!!!!!!" << std::endl << "abs error: " << fabs(error) << std::endl;
    setMotorPowers(0, 0);
    outputFile << "END OF TURN" << std::endl;
}

void Robot::setMotorPowers(double lPower, double rPower)
{
    l.setPower(lPower);
    r.setPower(rPower);
    printf( "\tlPower: %.3f", lPower);
    printf("\trPower: %.3f", rPower);
    if (fabs(lPower) > 1 && fabs(rPower) > 1)
    {
       printf("\tTRIED TO SET POWER GREATER THAN 1\n"); 
    }
    
}