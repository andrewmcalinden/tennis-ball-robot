#ifndef ROBOT_H
#define ROBOT_H

#include "../motor/motor.h"
#include "../encoder/encoder.h"
class Robot
{
    private:
    Motor l;
    Motor r;

    Encoder encoderL;
    Encoder encoderR;

    public:
    Robot(unsigned char lMotorDirPin, unsigned char lMotorPowerPin, unsigned char rMotorDirPin, unsigned char rMotorPowerPin,
            double initialX, double initialY, double initialTheta,
            unsigned char lEncoderPin1, unsigned char lEncoderPin2, unsigned char rEncoderPin1, unsigned char rEncoderPin2);

    void goStraight(double inches, double kp, double ki, double kd, double f);
    void turnHeading(double finalAngle, double kp, double ki, double kd, double f); //in degrees, turns to that heading (field centric)

    void setMotorPowers(double lPower, double rPower);
};
#endif