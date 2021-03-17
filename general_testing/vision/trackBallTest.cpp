#include "../vision/ballDetector.h"
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>

#include <iostream>

int main()
{
    vector<Ball> boundingBoxes = getBoundingBoxes();
    while (boundingBoxes.size() == 0) //while we don't see any balls
    {
        boundingBoxes = getBoundingBoxes();
    }
    trackBall(boundingBoxes.at(0));
}