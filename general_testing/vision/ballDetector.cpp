#include "ballDetector.h"
#include <iostream>

using namespace cv;
using namespace std;

int hmin = 37, smin = 106, vmin = 123;
int hmax = 53, smax = 208, vmax = 255;

VideoCapture cap;

void startCamera()
{
    cap.open(0);
    if (!cap.isOpened())
    {
        std::cout << "Could not initialize capturing..." << endl;
    }
}

vector<Point> getCenters()
{
    Mat img, imgCrop, imgHSV, imgMask, imgDilate;

    cap.grab();
    cap.retrieve(img);

    Size s = img.size();
    int w = s.width;
    int h = s.height;

    int leftSide = w * .45;
    Rect r(leftSide, 0, w * .1, h);

    imgCrop = img(r);

    cvtColor(imgCrop, imgHSV, COLOR_BGR2HSV);

    Scalar lower(hmin, smin, vmin);
    Scalar upper(hmax, smax, vmax);
    inRange(imgHSV, lower, upper, imgMask);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    dilate(imgMask, imgDilate, kernel);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(imgDilate, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    drawContours(img, contours, -1, Scalar(255, 0, 255), 1);

    vector<Point> centers;
    for (vector<Point> &contour : contours)
    {
        Moments m = moments(contour);
        double xCenter = m.m10 / m.m00;
        double yCenter = m.m01 / m.m00;

        stringstream point;
        point << "(" << xCenter << ", " << yCenter << ")";
        string text = point.str();

        Point p((int)xCenter, (int)yCenter);
        centers.push_back(p);

        putText(img, text, p, FONT_HERSHEY_DUPLEX, .3, Scalar(255, 255, 255), .2);
    }
    
    // imshow("crop", imgCrop);
    // imshow("mask", imgMask);
    // imshow("dilated", imgDilate);
    // imshow("orig", img);
    return centers;
}
