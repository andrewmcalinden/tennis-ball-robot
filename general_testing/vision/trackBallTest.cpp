#include "../vision/ballDetector.h"
#include <iostream>
#include <thread>

int main()
{
    std::vector<cv::Rect2d> boundingBoxes = getBoundingBoxes();
    while (cv::waitKey(1) != 32) //while we don't see any balls
    {
        boundingBoxes = getBoundingBoxes();
    }
    std::thread th(trackBall, boundingBoxes.at(0));
    th.join();
    // while(cv::waitKey(1) != 32)
    // {
    //     std::cout << getBallX() << std::endl;
    // }
    // stopTracking();
}