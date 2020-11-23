#include "robot.h"

#define LEFT_MOTOR_DIR_PIN 0
#define LEFT_MOTOR_POWER_PIN 1
#define RIGHT_MOTOR_DIR_PIN 2
#define RIGHT_MOTOR_POWER_PIN 3

#define INITIAL_X 0
#define INITIAL_Y 0
#define INITIAL_THETA 0

int EncoderL::position = 0;
unsigned char EncoderL::state = 0;

int EncoderR::position = 0;
unsigned char EncoderR::state = 0;

int main()
{
    EncoderL::begin();
    EncoderR::begin();
    Robot r(LEFT_MOTOR_DIR_PIN, LEFT_MOTOR_POWER_PIN, RIGHT_MOTOR_DIR_PIN, RIGHT_MOTOR_POWER_PIN, INITIAL_X, INITIAL_Y, INITIAL_THETA);
    // r.goStraight(10, .1, 0, .1, .1);
    r.printEncoders();
}