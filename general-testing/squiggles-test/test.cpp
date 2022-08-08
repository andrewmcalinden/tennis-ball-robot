#include "squiggles.hpp"
#include <ctime>

#include "../encoder/encoder.h"
#include "../motor/motor.h"

#define PULSES_PER_REV 1440.0
#define WHEEL__DIAMETER 0.063627 //meters

const double MAX_VEL = .3;     // in meters per second
const double MAX_ACCEL = 1.0;   // in meters per second per second
const double MAX_JERK = 2;    // in meters per second per second per second
const double ROBOT_WIDTH = 0.253575989275506; // in meters

squiggles::Constraints constraints = squiggles::Constraints(MAX_VEL, MAX_ACCEL, MAX_JERK);
squiggles::SplineGenerator generator = squiggles::SplineGenerator(
    constraints,
    std::make_shared<squiggles::TankModel>(ROBOT_WIDTH, constraints));

Motor l(22, 23);
Motor r(27, 26);

Encoder eL(0, 7);
Encoder eR(3, 2);

double startTime = 0;

double getTime()
{
    return std::clock() / ((double)CLOCKS_PER_SEC) - startTime;
}

int main()
{
    std::vector<squiggles::ProfilePoint> path = generator.generate({ squiggles::Pose(0.0, 0.0, 1.0),
                                                                    squiggles::Pose(3, 1.5, 1.0) });

    double kp = 10, ki = 10;

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

        std::cout << vTargetL << " " << vTargetR << std::endl;

        double nextTime = path.at(i + 1).time;
        double prevTime = getTime();
        double lastUpdate = prevTime;
        while (getTime() < nextTime)
        {
            //pid to needed velocities
            double currentTime = getTime();
            double dt = currentTime - prevTime;

            double currentPosL = eL.read() * WHEEL__DIAMETER * M_PI / PULSES_PER_REV;
            double posChangeL = currentPosL - prevPosL;

            double currentPosR = eR.read() * WHEEL__DIAMETER * M_PI / PULSES_PER_REV;
            double posChangeR = currentPosR - prevPosR;

            if (currentTime - lastUpdate > .05)
            {
                velocityL = posChangeL / (currentTime - lastUpdate);
                velocityR = posChangeR / (currentTime - lastUpdate);

                lastUpdate = currentTime;
                prevPosL = currentPosL;
                prevPosR = currentPosR;
            }

            double pL = vTargetL - velocityL;
            double pR = vTargetR - velocityR;

            iL += dt * (prevErrorL + pL) / 2.0;
            iR += dt * (prevErrorR + pR) / 2.0;

            double outputL = (kp * pL) + (ki * iL);
            if (outputL < 0) outputL -= .12;
            else outputL += .12;

            double outputR = (kp * pR) + (ki * iR);
            if (outputR < 0) outputR -= .12;
            else outputR += .12;

            l.setPower(outputL);
            r.setPower(outputR);

            prevErrorL = pL;
            prevErrorR = pR;

            prevTime = currentTime;
        }
        lastVL = velocityL;
        lastVR = velocityR;
    }
    //follow last point here, can probably just ignore ngl
    l.setPower(0);
    r.setPower(0);
}