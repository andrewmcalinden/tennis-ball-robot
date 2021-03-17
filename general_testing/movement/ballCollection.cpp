#include "robot.h"
#include "../odometry/odometry.h"
#include <wiringPi.h>
#include <iostream>

#define LEFT_MOTOR_DIR_PIN 22
#define LEFT_MOTOR_POWER_PIN 23
#define RIGHT_MOTOR_DIR_PIN 27
#define RIGHT_MOTOR_POWER_PIN 26

#define INITIAL_X 0
#define INITIAL_Y 0
#define INITIAL_THETA 0

#define L_ENCODER_PIN1 7
#define L_ENCODER_PIN2 0
#define R_ENCODER_PIN1 2
#define R_ENCODER_PIN2 3

int main()
{
    startCamera();
    while (getBalls().size() == 0) //turn until we see a single ball
    {
        r.setMotorPowers(.2, -.2);
        delay(20);
    }

    //turn until this ball is at the left of the screen since we initially saw it at the right
    turnPixel(0, .37, 0, .0006, .12);
}