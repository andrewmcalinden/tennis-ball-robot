#pragma once

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>

void setMask();

//std::vector<Ball> getBalls();           //returns x, y of center of ball and area of ball
std::vector<cv::Rect2d> getBoundingBoxes(); //returns bounding boxes around each ball in the video

int getImageWidth();
int getImageHeight();

double getBallX();
double getBallY();

void trackBall(cv::Rect2d initialBBox); //draws bounding box around the ball initially passed as a parameter
void stopTracking();
void startTracking(cv::Rect2d initialBB);

std::atomic<bool> track;
