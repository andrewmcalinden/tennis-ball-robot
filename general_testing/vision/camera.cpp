#include "camera.h"
#include <iostream>

Camera::Camera(unsigned char index)
{
    cap.open(index);
    if (!cap.isOpened())
    {
        std::cout << "Could not initialize capturing..." << std::endl;
    }
    std::cout << "Not set" << std::endl;
    cap.set(cv::CAP_PROP_BUFFERSIZE, 1); //really makes the camera store 3 images
    std::cout << "set" << std::endl;

    cv::Mat test;
    cap.read(test);

    imageWidth = test.cols;
    imageHeight = test.rows;
}

cv::Mat Camera::getFrame()
{
    cv::Mat img;
    //3 images in buffer
    for (int i = 0; i < 3; i++)
    {
        cap.read(img);
    }
    return img;
}

int Camera::getImageWidth()
{
    return imageWidth;
}

int Camera::getImageHeight()
{
    return imageHeight;
}

void Camera::setResolution(int w, int h)
{
    cap.set(cv::CAP_PROP_FRAME_WIDTH, w);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, h);
}