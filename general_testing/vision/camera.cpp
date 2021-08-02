#include "camera.h"

void Camera::Camera(unsigned char index)
{
    cap.open(0);
    if (!cap.isOpened())
    {
        std::cout << "Could not initialize capturing..." << endl;
    }
    cap.set(cv::CAP_PROP_BUFFERSIZE, 1); //really makes the camera store 3 images
    
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