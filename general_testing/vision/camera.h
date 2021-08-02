#pragma once

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class Camera
{
    private:
    cv::VideoCapture cap;
    int imageWidth;
    int imageHeight;

    public:
    Camera(unsigned char index);
    cv::Mat getFrame();
    int getImageWidth();
    int getImageHeight();
};