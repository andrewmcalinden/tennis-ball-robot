#include "experimentalRobot.h"
#include "../odometry/odometry.h"
#include "../math/mathUtil.h"
#include "../math/pose.h"
#include <cmath>
#include <iostream>

ExperimentalRobot::ExperimentalRobot(int lMotorDirPin, int lMotorPowerPin, int rMotorDirPin, int rMotorPowerPin,
                                     double initialX, double initialY, double initialTheta,
                                     int lEncoderPin1, int lEncoderPin2, int rEncoderPin1, int rEncoderPin2)
    : l{lMotorDirPin, lMotorPowerPin}, r{rMotorDirPin, rMotorPowerPin}, encoderL{lEncoderPin1, lEncoderPin2}, encoderR{rEncoderPin1, rEncoderPin2}, startPos{initialX, initialY} //initialize motors and encoders
{
    setPose(initialX, initialY, initialTheta);
    numMovements = 0;
    currentIndex = 0;
}

void ExperimentalRobot::setMotorPowers(double lPower, double rPower)
{
    l.setPower(lPower);
    r.setPower(rPower);
    std::cout << "lPower: " << lPower << "  rPower: " << rPower << "\n";
}

void ExperimentalRobot::run()
{
    while (numMovements > 0)
    {
        updatePos(encoderL.read(), encoderR.read());
        pose currentPose;
        currentPose.x = getX();
        currentPose.y = getY();
        currentPose.heading = getHeading();

        Movement* currentMovement = &(movements.at(currentIndex));
        currentMovement->beginMovement(currentPose);

        while (!currentMovement->finished())
        {
            updatePos(encoderL.read(), encoderR.read());

            currentMovement->updatePower(currentPose);
            motorPowers m = currentMovement->getPowers();
            setMotorPowers(m.lPower, m.rPower);
        }
        numMovements--;
        currentIndex--;
    }
}

void ExperimentalRobot::addMovement(Movement t)
{
    movements.push_back(t);
    numMovements++;
}