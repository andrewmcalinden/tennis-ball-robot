#include "robot.h"
#include "../odometry/odometry.h"
#include "../math/mathUtil.h"
#include <cmath>
#include <iostream>

Robot::Robot(int lMotorDirPin, int lMotorPowerPin, int rMotorDirPin, int rMotorPowerPin,
             double initialX, double initialY, double initialTheta,
             int lEncoderPin1, int lEncoderPin2, int rEncoderPin1, int rEncoderPin2)
    : l{lMotorDirPin, lMotorPowerPin}, r{rMotorDirPin, rMotorPowerPin}, encoderL{lEncoderPin1, lEncoderPin2}, encoderR{rEncoderPin1, rEncoderPin2}, startPos{initialX, initialY} //initialize motors and encoders
{
    setPose(initialX, initialY, initialTheta);
    numMovements = 0;
    currentIndex = 0;
}

void Robot::setMotorPowers(double lPower, double rPower)
{
    l.setPower(lPower);
    r.setPower(rPower);
    std::cout << "lPower: " << lPower << "  rPower: " << rPower << "\n";
}

void Robot::run()
{
    
    while (numMovements > 0)
    {
        double fakeHeading = 0;
        updatePos(encoderL.read(), encoderR.read());

        Turn currentMovement = turns.at(currentIndex);
        currentMovement.beginMovement(getHeading());

        while(!currentMovement.finished())
        {
            updatePos(encoderL.read(), encoderR.read());

            currentMovement.updatePower(fakeHeading);
            motorPowers m = currentMovement.getPowers();
            setMotorPowers(m.lPower, m.rPower);
            fakeHeading += .0001;
        }
        numMovements--;
        currentIndex--;
    }
}

void Robot::addMovement(Turn t)
{
    turns.push_back(t);
}