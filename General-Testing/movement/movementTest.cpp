#include "robot.h"
#include <functional>
#include <vector>

#define LEFT_MOTOR_DIR_PIN 0
#define LEFT_MOTOR_POWER_PIN 1
#define RIGHT_MOTOR_DIR_PIN 2
#define RIGHT_MOTOR_POWER_PIN 3

#define INITIAL_X 0
#define INITIAL_Y 0
#define INITIAL_THETA 0

int main()
{
    EncoderL::begin();
    EncoderR::begin();

    Robot r(LEFT_MOTOR_DIR_PIN, LEFT_MOTOR_POWER_PIN, RIGHT_MOTOR_DIR_PIN, RIGHT_MOTOR_POWER_PIN, INITIAL_X, INITIAL_Y, INITIAL_THETA);

    //add all movements to the vector of movements
    movements.push_back(std::bind(&Robot::goStraight(20, .1, .1, .1, .1), r));

    for (FuncVector::iterator currentFunc = functions.begin(); currentFunc != functions.end(); currentFunc++)
    {
        updatePos(EncoderL::read(), EncoderR::read());
        //update will call the current movement method from the movement vector which is in the robot class
        //those methods set the motor powers
        r.update();
    }
}