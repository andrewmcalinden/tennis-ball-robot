#include "robot.h"
#include "wiringPi.h"

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
    r.turnHeading(90, .37, 0, .00004, .08); //WORKS GOOD, NO OVERSHOOT
    // r.turnHeading(-30, .17, 0, .0001, .04);
    // r.turnHeading(90, .17, 0, .0001, .04);
    // r.turnHeading(0, .17, 0, .0001, .04);
    //r.goStraight(20, .4, 0, 0, .04);
}