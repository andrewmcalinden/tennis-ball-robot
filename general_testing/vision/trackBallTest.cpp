#include "../vision/ballDetector.h"
#include <iostream>

int main()
{
    std::vector<Rect2d> boundingBoxes = getBoundingBoxes();
    while (boundingBoxes.size() == 0) //while we don't see any balls
    {
        boundingBoxes = getBoundingBoxes();
    }
    trackBall(boundingBoxes.at(0));
}