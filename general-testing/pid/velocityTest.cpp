#include <iostream>
#include <ctime>
#include <cmath>
#include <fstream>

#include "../encoder/encoder.h"
#include "../motor/motor.h"

#define PULSES_PER_REV 1440.0
#define WHEEL__DIAMETER 0.063627 //meters

int main()
{
    std::ifstream constants("constants.txt");
    double vTarget;
    constants >> vTarget;

    double kp, ki, kd, kf;
    constants >> kp >> ki >> kd >> kf;

    std::ofstream points("points.txt");
    std::ofstream outputs("outputs.txt");
    Motor l(22, 23);
    Motor r(27, 26);
    Encoder e(0, 7);

    double prevPos = e.read() * WHEEL__DIAMETER * M_PI / PULSES_PER_REV;
    double prevTime = std::clock() / ((double)CLOCKS_PER_SEC);
    double lastUpdate = std::clock() / ((double)CLOCKS_PER_SEC); //prevTime;
    double prevError = vTarget;

    double velocity = 0;

    double i = 0;
    while (true)
    {
        double currentTime = std::clock() / ((double)CLOCKS_PER_SEC);
        // double currentPos = e.read() * WHEEL__DIAMETER * M_PI / PULSES_PER_REV;

        // double posChange = currentPos - prevPos;
        // double dt = currentTime - prevTime;

        if (currentTime - lastUpdate > .05)
        {
            double dt = currentTime - lastUpdate;

            double currentPos = e.read() * WHEEL__DIAMETER * M_PI / PULSES_PER_REV;
            double posChange = currentPos - prevPos;

            velocity = posChange / (dt);

            double error = vTarget - velocity;
            double p = error;

            i += dt * (prevError + error) / 2.0;

            double d = (error - prevError) / dt;

            double output = (kp * p) + (ki * i) + (kd * d) + kf;

            l.setPower(output);
            r.setPower(-output);

            outputs << currentTime << ", " << output << std::endl;

            lastUpdate = currentTime;
            prevPos = currentPos;

            prevError = error;
            prevTime = currentTime;

            points << currentTime << ", " << velocity << std::endl;
        }
    }
}