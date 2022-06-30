#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include "../general_testing/vision/camera.h"

using namespace cv;
using namespace std;

int main()
{
    string classifier = "data/cascade.xml";

    CascadeClassifier ballCascade;
    ballCascade.load(classifier);

    Camera cam(0);
    cam.setResolution(1280, 720);

    while(1)
    {
        Mat img, imgGray;
        img = cam.getFrame();
        cvtColor(img, imgGray, COLOR_BGR2GRAY);

        vector<Rect> balls;
        ballCascade.detectMultiScale(imgGray, balls, 2, 2);

        for (int i = 0; i < balls.size(); i++)
        {
            rectangle(img, balls[i].tl(), balls[i].br(), Scalar(255, 0, 255), 3);
        }

        imshow("found balls", img);
        waitKey(1);
    }
}