#include "../vision/ballDetector.h"
#include <iostream>

int main()
{
    std::vector<cv::Rect2d> boundingBoxes = getBoundingBoxes();
    while (boundingBoxes.size() < 99) //while we don't see any balls
    {
        boundingBoxes = getBoundingBoxes();
        cv::waitKey(1);
    }
    //trackBall(boundingBoxes.at(0));
}