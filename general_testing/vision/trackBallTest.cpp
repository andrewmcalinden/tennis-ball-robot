#define DIRECTION_PIN_FORWARD_LEFT 22
#define POWER_PIN_LEFT 23
#define DIRECTION_PIN_FORWARD_RIGHT 27
#define POWER_PIN_RIGHT 26

#include "../vision/ballDetector.h"
#include"../motor/motor.h"
#include <iostream>


int main()
{
    Motor motorL(DIRECTION_PIN_FORWARD_LEFT, POWER_PIN_LEFT);
    Motor motorR(DIRECTION_PIN_FORWARD_RIGHT, POWER_PIN_RIGHT);

    setMask();
    std::vector<cv::Rect2d> boundingBoxes = getBoundingBoxes();
    while (cv::waitKey(1) != 32) //while we don't see any balls
    {
        boundingBoxes = getBoundingBoxes();
    }
    startTracking(boundingBoxes.at(0));
    motorL.setPower(.25);
    motorR.setPower(-.25);
    while(getBallX() < 600)
    {
        //std::cout << getBallX() << std::endl;
    }
    stopTracking();
}