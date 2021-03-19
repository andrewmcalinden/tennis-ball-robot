#include "../vision/ballDetector.h"
#include <iostream>

int main()
{
    std::vector<cv::Rect2d> boundingBoxes = getBoundingBoxes();
    while (cv::waitKey(1) != 32) //while we don't see any balls
    {
        boundingBoxes = getBoundingBoxes();
    }
    startTracking(boundingBoxes.at(0));
    while(getBallX() < 500)
    {
        std::cout << getBallX() << std::endl;
    }
    stopTracking();
}