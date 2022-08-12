#include "squiggles.hpp"
#include <ctime>
#include <fstream>

#include "../encoder/encoder.h"
#include "../motor/motor.h"

#define PULSES_PER_REV 1440.0
#define WHEEL__DIAMETER 0.063627 //meters

const double MAX_VEL = .6;     // in meters per second
const double MAX_ACCEL = 1;   // in meters per second per second
const double MAX_JERK = 2;    // in meters per second per second per second
const double ROBOT_WIDTH = 0.253575989275506; // in meters

squiggles::Constraints constraints = squiggles::Constraints(MAX_VEL, MAX_ACCEL, MAX_JERK);
squiggles::SplineGenerator generator = squiggles::SplineGenerator(
    constraints,
    std::make_shared<squiggles::TankModel>(ROBOT_WIDTH, constraints));

double startTime = 0;

double getTime()
{
    return std::clock() / ((double)CLOCKS_PER_SEC) - startTime;
}

int main()
{
    Motor l(22, 23);
    Motor r(27, 26);

    Encoder eL(0, 7);
    Encoder eR(3, 2);

    std::vector<squiggles::ProfilePoint> path = generator.generate({squiggles::Pose(0.0, 0.0, 1.0),
                                                                    squiggles::Pose(.18, 1.07, .5),
                                                                    squiggles::Pose(1.2, 1.34, 0),
                                                                    squiggles::Pose(2.37, 1.4, -.5)});

    std::ofstream pointsL("pointsL.txt");
    std::ofstream pointsR("pointsR.txt");

    std::ofstream outputsL("outputsL.txt");
    std::ofstream outputsR("outputsR.txt");

    double kp = 2, ki = 1;

    double lastVL = 0;
    double lastVR = 0;

    startTime = getTime(); //getTime() returns time after this point
    for (int i = 0; i < path.size() - 1; i++)
    {

        squiggles::ProfilePoint cur = path.at(i);

        double vTargetL = cur.wheel_velocities[0];
        double vTargetR = cur.wheel_velocities[1];

        double prevPosL = eL.read() * WHEEL__DIAMETER * M_PI / PULSES_PER_REV;
        double velocityL = lastVL;
        double iL = 0;
        double prevErrorL = vTargetL - velocityL;

        double prevPosR = eR.read() * WHEEL__DIAMETER * M_PI / PULSES_PER_REV;
        double velocityR = lastVR;
        double iR = 0;
        double prevErrorR = vTargetR - velocityR;

        //std::cout << vTargetL << " " << vTargetR << std::endl;

        double nextTime = path.at(i + 1).time;
        double prevTime = getTime();
        double lastUpdate = prevTime;
        while (getTime() < nextTime)
        {
            //pid to needed velocities
            double currentTime = getTime();

            if (currentTime - lastUpdate > .05)
            {
                double dt = currentTime - prevTime;

                double currentPosL = eL.read() * WHEEL__DIAMETER * M_PI / PULSES_PER_REV;
                double posChangeL = currentPosL - prevPosL;

                double currentPosR = eR.read() * WHEEL__DIAMETER * M_PI / PULSES_PER_REV;
                double posChangeR = currentPosR - prevPosR;

                velocityL = posChangeL / (currentTime - lastUpdate);
                velocityR = posChangeR / (currentTime - lastUpdate);

                double pL = vTargetL - velocityL;
                double pR = vTargetR - velocityR;

                iL += dt * (prevErrorL + pL) / 2.0;
                iR += dt * (prevErrorR + pR) / 2.0;

                double outputL = (kp * pL) + (ki * iL);
                if (vTargetL < 0) outputL -= .07;
                else outputL += .07;

                double outputR = (kp * pR) + (ki * iR);
                if (vTargetR < 0) outputR -= .07;
                else outputR += .07;

                l.setPower(outputL);
                r.setPower(outputR);

                outputsL << currentTime << ", " << outputL << std::endl;
                outputsR << currentTime << ", " << outputR << std::endl;

                pointsL << currentTime << ", " << velocityL << std::endl;
                pointsR << currentTime << ", " << velocityR << std::endl;

                prevErrorL = pL;
                prevErrorR = pR;

                prevPosL = currentPosL;
                prevPosR = currentPosR;

                prevTime = currentTime;
                lastUpdate = currentTime;
            }
        }
        lastVL = velocityL;
        lastVR = velocityR;
    }
    //follow last point here, can probably just ignore ngl
    l.setPower(0);
    r.setPower(0);
}