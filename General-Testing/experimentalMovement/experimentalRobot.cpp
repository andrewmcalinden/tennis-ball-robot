#include "experimentalRobot.h"
#include "../odometry/odometry.h"
#include "../math/mathUtil.h"
#include <cmath>
#include <iostream>

ExperimentalRobot::ExperimentalRobot(int lMotorDirPin, int lMotorPowerPin, int rMotorDirPin, int rMotorPowerPin,
                                     double initialX, double initialY, double initialTheta,
                                     int lEncoderPin1, int lEncoderPin2, int rEncoderPin1, int rEncoderPin2)
    : l{lMotorDirPin, lMotorPowerPin}, r{rMotorDirPin, rMotorPowerPin}, encoderL{lEncoderPin1, lEncoderPin2}, encoderR{rEncoderPin1, rEncoderPin2}//initialize motors and encoders
{
    setPose(initialX, initialY, initialTheta);
}

void ExperimentalRobot::setMotorPowers(double lPower, double rPower)
{
    l.setPower(lPower);
    r.setPower(rPower);
    std::cout << "lPower: " << lPower << "  rPower: " << rPower << "\n";
}

void ExperimentalRobot::run()
{
    for (auto it = movements.begin(); it != movements.end(); ++it)
    {
        updatePos(encoderL.read(), encoderR.read());
        pose currentPose;
        currentPose.x = getX();
        currentPose.y = getY();
        currentPose.heading = getHeading();

        it->beginMovement(currentPose);

        while (!it->finished())
        {
            updatePos(encoderL.read(), encoderR.read());

            it->updatePower(currentPose);
            motorPowers m = it->getPowers();
            setMotorPowers(m.lPower, m.rPower);
        }
    }
}

void ExperimentalRobot::addMovement(Movement t)
{
    movements.push_back(t);
}