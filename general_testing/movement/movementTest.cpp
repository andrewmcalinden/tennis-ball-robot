#include "robot.h"
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

#define COUNT_INPUT_PIN 12

int main()
{
    Robot r(LEFT_MOTOR_DIR_PIN, LEFT_MOTOR_POWER_PIN, RIGHT_MOTOR_DIR_PIN, RIGHT_MOTOR_POWER_PIN, INITIAL_X, INITIAL_Y, INITIAL_THETA, L_ENCODER_PIN1, L_ENCODER_PIN2, R_ENCODER_PIN1, R_ENCODER_PIN2, COUNT_INPUT_PIN);
    r.goToPos(0, 10,
              .5, 0, .05, .12, .5,
              .37, 0, .0006, .12);
    // r.goToPos(80, 160,
    //           .37, 0, .002, .12, .5,
    //           .37, 0, .0006, .12);
    // r.goToPos(0, 220,
    //           .37, 0, .002, .12, .5,
    //           .37, 0, .0006, .12);
    // r.goToPos(-80, 220,
    //           .37, 0, .002, .12, .5,
    //           .37, 0, .0006, .12);
    // r.goToPos(-160, 140,
    //           .37, 0, .002, .12, .5,
    //           .37, 0, .0006, .12);
    // r.goToPos(-160, 80,
    //           .37, 0, .002, .12, .5,
    //           .37, 0, .0006, .12);
    // r.goToPos(-80, 0,
    //           .37, 0, .002, .12, .5,
    //           .37, 0, .0006, .12);
    // r.goToPos(0, 0,
    //           .37, 0, .002, .12, .5,
    //           .37, 0, .0006, .12);
              
    // r.turnHeading(90, .37, 0, .0006, .12);
    //BEST CONSTANTS SO FAR WITH NEW METHOD
    //r.turnHeading(90, .37, 0, .0006, .12);
    //r.goStraight(-75, .37, 0, .002, .12, .7);
}