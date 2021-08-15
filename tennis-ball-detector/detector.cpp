#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <filesystem>
#include <sstream>

using namespace cv;
using namespace std;

int main()
{
    string classifier = "data/cascade.xml";

    CascadeClassifier ballCascade;
    ballCascade.load(classifier);

    for (int num = 14; num <= 30; num++)
    {
        stringstream ss;
        ss << "images/image_" << num << ".png";

        string path = ss.str();
        //cout << path << endl;
        Mat img, imgGray;
        img = imread(path);
        cvtColor(img, imgGray, COLOR_BGR2GRAY);

        vector<Rect> balls;
        ballCascade.detectMultiScale(imgGray, balls, 2, 2);

        for (int i = 0; i < balls.size(); i++)
        {
            rectangle(img, balls[i].tl(), balls[i].br(), Scalar(255, 0, 255), 3);
        }

        imshow("found balls", img);
        waitKey(0);
    }
}