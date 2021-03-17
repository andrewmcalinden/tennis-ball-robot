#pragma once

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

struct Ball
{
    double area;
    Point center;
};

void startCamera();
std::vector<Ball> getBalls(); //returns x, y of center of ball and area of ball
std::vector<Rect2d> getBoundingBoxes(); //returns bounding boxes around each ball in the video