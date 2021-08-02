#include "../vision/ballDetector.h"
#include <iostream>

int main()
{
    setMask();
    std::vector<cv::Rect2d> boundingBoxes = getBoundingBoxes();
    while (cv::waitKey(1) != 32) //while we don't see any balls
    {
        boundingBoxes = getBoundingBoxes();
    }
    startTracking(boundingBoxes.at(0));
    while(getBallX() < 600)
    {
        std::cout << getBallX() << std::endl;
    }
    stopTracking();
}