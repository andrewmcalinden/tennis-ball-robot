#include "robot.h"
#include "../odometry/odometry.h"
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
    Robot r(LEFT_MOTOR_DIR_PIN, LEFT_MOTOR_POWER_PIN, RIGHT_MOTOR_DIR_PIN, RIGHT_MOTOR_POWER_PIN, INITIAL_X, INITIAL_Y, INITIAL_THETA, L_ENCODER_PIN1, L_ENCODER_PIN2, R_ENCODER_PIN1, R_ENCODER_PIN2);
    int i = 4;
    int start = 90;
    while (i--)
    {
        r.turnHeading(90, .37, 0, .0006, .12);
        r.goStraight(75, .37, 0, .002, .12, .7);
        start += 90;
    }

    //these constants work pretty well: fast but some oscilation/overshoot USING OLD BAD TIME
    //r.turnHeading(90, .37, .00003, .00004, .12);
    //r.goStraight(25, .45, .00026, .0005, .08);

    //BEST CONSTANTS SO FAR WITH NEW METHOD
    //r.turnHeading(90, .37, 0, .0006, .12);
    //r.goStraight(-75, .37, 0, .002, .12, .7);
}