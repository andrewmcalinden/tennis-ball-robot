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

    for (int i = 0; i < 4; i++)
    {
        for (double d = .20; d <= .5; d += .05)
        {
            motorL.setPower(d);
            motorR.setPower(-d);
            delay(100);
        }
        delay(500);
    }

    while (cv::waitKey(1) != 32)
    {
        //std::cout << getBallX() << std::endl;
    }
    motorL.setPower(0);
    motorR.setPower(0);
    stopTracking();
}