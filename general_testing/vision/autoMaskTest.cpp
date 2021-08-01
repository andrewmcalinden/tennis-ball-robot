#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    VideoCapture cap(0);
    Mat img;
    Mat hsv;

    if (!cap.isOpened())
    {
        cout << "Could not initialize capturing..." << endl;
        return 0;
    }

    while (1)
    {
        cap.grab();
        cap.retrieve(img);

        cvtColor(img, hsv, CV_BGR2HSV);
        int midCol = hsv.cols / 2;
        int midRow = hsv.rows / 2;
        Vec3b values = hsv.at<Vec3b>(midRow, midCol);

        int h = values.val[0]; //hue
        int s = values.val[1]; //saturation
        int v = values.val[2]; //value

        cout << "h: " << h << "\ts: " << s << "\tv: " << v << endl;

        imshow("rgb", img);
        imshow("hsv", hsv);

        while (waitKey(1) != ' '){} //do nothing
    }
}