#include "robot.h"

#define LEFT_MOTOR_DIR_PIN 0
#define LEFT_MOTOR_POWER_PIN 1
#define RIGHT_MOTOR_DIR_PIN 2
#define RIGHT_MOTOR_POWER_PIN 3

#define INITIAL_X 0
#define INITIAL_Y 0
#define INITIAL_THETA 0


PI_THREAD(localize)
{
    while (true)
    {
        updatePos(EncoderL::read(), EncoderR::read());
    }
}

int main()
{
    EncoderL::begin();
    EncoderR::begin();

    piThreadCreate(localize);

    Robot r(LEFT_MOTOR_DIR_PIN, LEFT_MOTOR_POWER_PIN, RIGHT_MOTOR_DIR_PIN, RIGHT_MOTOR_POWER_PIN, INITIAL_X, INITIAL_Y, INITIAL_THETA);
    r.goStraight(20, .1, 0, .1, .1);

}