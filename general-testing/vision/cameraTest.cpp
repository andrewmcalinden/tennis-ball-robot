#include "camera.h"
#include <iostream>

using namespace std;

int main()
{
    Camera c(0);
    cv::Mat frame;

    while (1)
    {
        frame = c.getFrame();
        cv::imshow("image", frame);
        cv::waitKey(0);
    }
}