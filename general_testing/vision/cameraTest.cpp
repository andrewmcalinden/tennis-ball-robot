#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <raspicam/raspicam_cv.h>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    VideoCapture cap(0);
    Mat img;

    if (!cap.isOpened())
    {
        cout << "Could not initialize capturing..." << endl;
        return 0;
    }

    while (1)
    {
        cap.grab();
        cap.retrieve(img);
        imshow("image", img);
        waitKey(1);
    }
}