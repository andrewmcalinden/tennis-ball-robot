#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <sstream>

using namespace cv;
using namespace std;
//day values
// int hmin = 37, smin = 106, vmin = 123;
// int hmax = 53, smax = 208, vmax = 255;

//burning night light values
int hmin = 38, smin = 0, vmin = 0;
int hmax = 82, smax = 208, vmax = 255;

int main()
{
    VideoCapture cap(0);
    Mat img, imgHSV, imgBlur, imgMask, imgResize, imgDilate;

    if (!cap.isOpened())
    {
        cout << "Could not initialize capturing..." << endl;
        return 0;
    }
    
    
    namedWindow("Trackbars", (640, 200));
    createTrackbar("hue min", "Trackbars", &hmin, 500);
    createTrackbar("hue max", "Trackbars", &hmax, 500);
    createTrackbar("sat min", "Trackbars", &smin, 500);
    createTrackbar("sat max", "Trackbars", &smax, 500);
    createTrackbar("val min", "Trackbars", &vmin, 500);
    createTrackbar("val max", "Trackbars", &vmax, 500);
    

    while(1)
    {
        cap.grab();
        cap.retrieve(img);
        // stringstream path;
        // path << "new_images/image_" << i << ".png";
        // img = imread(path.str());

        resize(img, imgResize, Size(), .75, .75);
        Size s = imgResize.size();
        cout << s.width << " " << s.height << endl;

        cvtColor(imgResize, imgHSV, COLOR_BGR2HSV);
       // GaussianBlur(imgHSV, imgBlur, Size(11, 11), 0);

        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        inRange(imgBlur, lower, upper, imgMask);

        Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
        dilate(imgMask, imgDilate, kernel);

        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        findContours(imgDilate, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        drawContours(imgResize, contours, -1, Scalar(255, 0, 255), 1);

        for (vector<Point> &contour : contours)
        {
            Moments m = moments(contour);
            double xCenter = m.m10 / m.m00;
            double yCenter = m.m01 / m.m00;

            stringstream point;
            point << "(" << xCenter << ", " << yCenter << ")";
            string text = point.str();

            putText(imgResize, text, Point((int)xCenter, (int)yCenter), FONT_HERSHEY_DUPLEX, .3, Scalar(255, 255, 255), .2);
            cout << xCenter << ", " << yCenter << endl;
        }

        line(imgResize, Point(62, 707), Point(716, 219), Scalar(0, 0, 255), 2);
        line(imgResize, Point(1218, 707), Point(564, 219), Scalar(0, 0, 255), 2);


        imshow("mask", imgMask);
        imshow("dilated masked", imgDilate);
        imshow("original", imgBlur);
        // char c=(char)waitKey(1);
        // while(c!=32){ c=(char)waitKey(1);} // do nothing
        waitKey(1);
    }
}