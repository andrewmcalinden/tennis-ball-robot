#ifndef ROBOT_H
#define ROBOT_H

#include "../motor/motor.h"
#include "../encoder/encoder.h"
#include "../vision/ballDetector.h"

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

    void goStraight(double inches, double kp, double ki, double kd, double f, double maxSpeed);
    void turnHeading(double finalAngle, double kp, double ki, double kd, double f); //in degrees, turns to that heading (field centric)
    void goToPos(double x, double y,
                 double kp_straight, double ki_straight, double kd_straight, double f_straight, double maxSpeed_straight,
                 double kp_turn, double ki_turn, double kd_turn, double f_turn);

    void setMotorPowers(double lPower, double rPower);

    void turnPixel(double finalPixel, double power, double f, cv::Rect2d initialBB);
    void curveToBall(cv::Rect2d initialBB, double power, double f);
    void goToBall();

    void countBalls();
};
#endif