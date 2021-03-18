#include "../vision/ballDetector.h"
#include <iostream>

int main()
{
    std::vector<cv::Rect2d> boundingBoxes = getBoundingBoxes();
    while (boundingBoxes.size() == 0) //while we don't see any balls
    {
        boundingBoxes = getBoundingBoxes();
        waitKey(1);
    }
    //trackBall(boundingBoxes.at(0));
}