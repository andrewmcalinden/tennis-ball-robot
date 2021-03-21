#include "robot.h"
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

#define COUNT_INPUT_PIN 12

int main()
{
    Robot r(LEFT_MOTOR_DIR_PIN, LEFT_MOTOR_POWER_PIN, RIGHT_MOTOR_DIR_PIN, RIGHT_MOTOR_POWER_PIN, INITIAL_X, INITIAL_Y, INITIAL_THETA, L_ENCODER_PIN1, L_ENCODER_PIN2, R_ENCODER_PIN1, R_ENCODER_PIN2, COUNT_INPUT_PIN);

    startCamera();
    while (getBoundingBoxes().size() == 0) //while we don't see any balls
    {
        r.setMotorPowers(.2, -.2);
        cv::waitKey(25);
    }
    r.setMotorPowers(0, 0);
    cv::waitKey(100);

    stopCamera();

    //now that we see a ball on the right of the screen, turn until it is at the left of the screen
    r.turnPixel(35, .05, .14, getBoundingBoxes().at(0));
}
