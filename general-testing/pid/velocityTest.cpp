#include <iostream>
#include <ctime>

#include <opencv2/highgui.hpp>

#include "../encoder/encoder.h"
#include "../motor/motor.h"

int main()
{
    double vTarget = 0; //in/sec
    cv::createTrackbar("Velocity Target", "Targets", &vTarget, 20); //max of 20in/sec, likely needs to be adjusted

    double kp = 0, ki = 0, kd = 0;
    cv::createTrackbar("kp", "PID", &kp, 1);
    cv::createTrackbar("ki", "PID", &ki, 1);
    cv::createTrackbar("kd", "PID", &kd, 1);

    Motor m(22, 23);
    Encoder e(7, 0);

    double prevPos = e.read();
    double prevTime = std::clock() / ((double) CLOCKS_PER_SEC);
    double prevError = vTarget;

    double i = 0;
    while (true)
    {
        double currentTime = std::clock() / ((double) CLOCKS_PER_SEC);
        double currentPos = e.read();

        double posChange = currentPos - prevPos;
        double dt = currentTime - prevTime;

        double velocity = posChange / dt;
        std::cout << velocity << std::endl;

        double error = velocity - vTarget;
        double p = error;

        i += dt * (prevError + error) / 2.0;

        double d = (error - prevError) / dt;

        double output = kp * p + ki * i + kd * d;
        m.setPower(output);

        prevPos = currentPos;
        prevTime = currentTime;
        prevError = error;
    }
}