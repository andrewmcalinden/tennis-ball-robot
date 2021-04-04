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

#define COUNT_INPUT_PIN 12
#define COLLECTOR_PIN 4

int main()
{
    Robot r(LEFT_MOTOR_DIR_PIN, LEFT_MOTOR_POWER_PIN, RIGHT_MOTOR_DIR_PIN, RIGHT_MOTOR_POWER_PIN, INITIAL_X, INITIAL_Y, INITIAL_THETA, L_ENCODER_PIN1, L_ENCODER_PIN2, R_ENCODER_PIN1, R_ENCODER_PIN2, COUNT_INPUT_PIN, COLLECTOR_PIN);

    startCamera();
    std::vector<cv::Rect2d> boxes = getBoundingBoxes();
    while (boxes.size() == 0) //while we don't see any balls
    {
        boxes = getBoundingBoxes();
        r.setMotorPowers(.2, -.2);
    }
    r.setMotorPowers(0, 0);
    cv::waitKey(200);

    stopCamera();
    startCamera();
    boxes = getBoundingBoxes();

    //now that we see a ball on the right of the screen, drive to it
    r.curveToBall(boxes.at(0), .3, .12);
}
