#pragma once

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>

struct Ball
{
    double area;
    cv::Point center;
};

void startCamera();
std::vector<Ball> getBalls(); //returns x, y of center of ball and area of ball
std::vector<cv::Rect2d> getBoundingBoxes(); //returns bounding boxes around each ball in the video
void trackBall(cv::Rect2d initialBBox); //draws bounding box around the ball initially passed as a parameter