#include "robot.h"
#include "../odometry/odometry.h"
#include "../math/mathUtil.h"
#include "../math/vector.h"
#include <wiringPi.h>
#include <cmath>
#include <ctime>
#include <iostream>
#include <fstream>

volatile int ballCount = 0;

void countBalls()
{
    ballCount++;
}

void Robot::startCollector()
{
    digitalWrite(ballCollectorPin, HIGH);
    delay(1000); //wait for collector to turn on
}

void Robot::stopCollector()
{
    digitalWrite(ballCollectorPin, LOW);
}

Robot::Robot(unsigned char lMotorDirPin, unsigned char lMotorPowerPin, unsigned char rMotorDirPin, unsigned char rMotorPowerPin,
             double initialX, double initialY, double initialTheta,
             unsigned char lEncoderPin1, unsigned char lEncoderPin2, unsigned char rEncoderPin1, unsigned char rEncoderPin2,
             unsigned char counterPin, unsigned char collectorPin)
    //initialize motors and encoders
    : l{lMotorDirPin, lMotorPowerPin}, r{rMotorDirPin, rMotorPowerPin},
      encoderL{lEncoderPin1, lEncoderPin2}, encoderR{rEncoderPin1, rEncoderPin2},
      ballCounterPin{counterPin}, ballCollectorPin{collectorPin}

{
    pinMode(ballCounterPin, INPUT);
    pinMode(collectorPin, OUTPUT);
    setPose(initialX, initialY, initialTheta);
    wiringPiISR(ballCounterPin, INT_EDGE_FALLING, &countBalls);
}

void Robot::goToPos
(double x, double y,
double kp_straight, double ki_straight, double kd_straight, double f_straight, double maxSpeed_straight,
double kp_turn, double ki_turn, double kd_turn, double f_turn)
{
    double xError = x - getX();
    double yError = y - getY();
    double angleToPoint = angleWrapDeg(toDegrees(atan2(yError, xError))) - 90; //subtract 90 becaue unit circle vs our angle system thing
    std::cout << "Angle: " << angleToPoint << std::endl;
    turnHeading(angleToPoint, kp_turn, ki_turn, kd_turn, f_turn);

    xError = x - getX();
    yError = y - getY();

    double distanceToPoint = hypot(xError, yError);
    std::cout << "Distance to Point: " << distanceToPoint << std::endl;
    goStraight(distanceToPoint, kp_straight, ki_straight, kd_straight, f_straight, maxSpeed_straight);
}

void Robot::goStraight(double inches, double kp, double ki, double kd, double f, double maxSpeed)
{
    double initialX = getX();
    double initialY = getY();

    const double initialHeadingRad = toRadians(getHeading() + 90); //add 90 because we want the right to be 0 but right now up is -90

    double additionalX = inches * cos(initialHeadingRad);
    double additionalY = inches * sin(initialHeadingRad);

    const double finalX = initialX + additionalX;
    const double finalY = initialY + additionalY;

    double error = inches;

    const double initialAngle = getHeading();

    double xError = finalX - getX();
    double yError = finalY - getY();

    double direction = angleWrapDeg(toDegrees(atan2(yError, xError)) - getHeading()); //if 90, forward, if -90, backward

    //scale powers up slowly
    // if (direction > 0 && direction < 180)
    // {
    //     for (double i = 0; i <= maxSpeed; i += .01)
    //     {
    //         setMotorPowers(i, i);
    //         delay(15);
    //     }
    // }
    // else
    // {
    //     for (double i = 0; i >= -maxSpeed; i -= .01)
    //     {
    //         setMotorPowers(i, i);
    //         delay(15);
    //     }
    // }

    //first, go max power until we are 3 feet away
    while (fabs(error) > 36)
    {
        updatePos(encoderL.read(), encoderR.read());
        xError = finalX - getX();
        yError = finalY - getY();

        direction = angleWrapDeg(toDegrees(atan2(yError, xError)) - getHeading()); //if 90, forward, if -90, backward

        error = hypot(xError, yError); //really abs(error)
        if (!(direction > 0 && direction < 180)) //90 is perfectly forwards, -90 is backwards
        {
            error *= -1;
        }

        double angle = getHeading();
        if (error > 0)
        {
            if (fabs(angle - initialAngle) > .125)
            {
                if (angleDiff(angle, initialAngle) < 0) //we are too far to the left
                {
                    setMotorPowers(maxSpeed, maxSpeed * .7);
                }
                else
                {
                    setMotorPowers(maxSpeed * .7, maxSpeed);
                }
            }
            else
            {
                setMotorPowers(maxSpeed, maxSpeed);
            }
        }
        else
        {
            if (fabs(angle - initialAngle) > .125)
            {
                if (angleDiff(angle, initialAngle) < 0) //we are too far to the left
                {
                    setMotorPowers(-maxSpeed * .7, -maxSpeed);
                }
                else
                {
                    setMotorPowers(-maxSpeed, -maxSpeed * .7);
                }
            }
            else
            {
                setMotorPowers(-maxSpeed, -maxSpeed);
            }
        }
    }

    std::ofstream outputFile("straightData.txt");

    std::clock_t timer;
    timer = std::clock();

    double pastTime = 0;
    double currentTime = ((std::clock() - timer) / (double)CLOCKS_PER_SEC);

    xError = finalX - getX();
    yError = finalY - getY();
    error = hypot(xError, yError);
    double pastError = error;

    double integral = 0;

    double firstTimeAtSetpoint = 0;
    double timeAtSetPoint = 0;
    bool atSetpoint = false;
    const unsigned char delayAmount = 20;
    int numDelays = 0;

    double pDivisor = fabs(inches);
    if (fabs(inches) > 36)
    {
        pDivisor = 36;
    }
    //once we are 3 feet away, use pid
    while (timeAtSetPoint < .3)
    {
        updatePos(encoderL.read(), encoderR.read());
        xError = finalX - getX();
        yError = finalY - getY();

        direction = angleWrapDeg(toDegrees(atan2(yError, xError)) - getHeading()); //if 90, forward, if -90, backward

        error = hypot(xError, yError); //really abs(error)

        currentTime = ((std::clock() - timer) / (double)CLOCKS_PER_SEC) + ((delayAmount / 1000.0) * numDelays);        
        double dt = currentTime - pastTime;

        if (!(direction > 0 && direction < 180)) //90 is perfectly forwards, -90 is backwards
        {
            error *= -1;
        }
        
        

        double proportional = error / pDivisor;
        integral += ((error + pastError) / 2.0)* dt;
        double derivative = (error - pastError) / dt;

        std::cout << "\n" << error;

        double power = kp * proportional + ki * integral + kd * derivative;
        outputFile << "Error: " << error << "\tP: " << proportional * kp << "\tI: " << integral * ki << "\tD: " << derivative * kd << "\tpower: " << power << "\tX: " << getX() << "\tY: " << getY() << std::endl;

        double angle = getHeading();

        if (power > 0)
        {
            if (fabs(angle - initialAngle) > .125)
            {
                if (angleDiff(angle, initialAngle) < 0) //we are too far to the left
                {
                    setMotorPowers(power + f, (power + f) * .7);
                }
                else
                {
                    setMotorPowers((power + f) * .7, power + f);
                }
            }
            else
            {
                setMotorPowers(power + f, power + f);
            }
        }
        else
        {
            if (fabs(angle - initialAngle) > .125)
            {
                if (angleDiff(angle, initialAngle) < 0) //we are too far to the left
                {
                    setMotorPowers((power - f) * .7, power - f);
                }
                else
                {
                    setMotorPowers(power - f, (power - f) * .7);
                }
            }
            else
            {
                setMotorPowers(power - f, power - f);
            }
        }

        if (fabs(error) < .25)
        {
            if (!atSetpoint)
            {
                atSetpoint = true;
                firstTimeAtSetpoint = currentTime;
            }
            else //at setpoint
            {
                timeAtSetPoint = currentTime - firstTimeAtSetpoint;
            }
        }
        else //no longer at setpoint
        {
            atSetpoint = false;
            timeAtSetPoint = 0;
        }
        pastTime = currentTime;
        pastError = error;
        delay(delayAmount);
        ++numDelays;
    }
    std::cout << "\nabs error: " << fabs(error) << std::endl;
    setMotorPowers(0, 0);
    outputFile.close();
}

void Robot::turnHeading(double finalAngle, double kp, double ki, double kd, double f)
{
    std::ofstream outputFile("turnData.txt");

    std::clock_t timer;
    timer = std::clock();

    double pastTime = 0;
    double currentTime = ((std::clock() - timer) / (double)CLOCKS_PER_SEC);

    const double initialHeading = getHeading();
    finalAngle = angleWrapDeg(finalAngle);

    const double initialAngleDiff = angleWrapDeg(initialHeading - finalAngle);
    outputFile << initialAngleDiff << std::endl;
    double error = angleDiff(getHeading(), finalAngle);
    double pastError = error;

    double firstTimeAtSetpoint = 0;
    double timeAtSetPoint = 0;
    bool atSetpoint = false;
    const unsigned char delayAmount = 20;
    int numDelays = 0;

    double integral = 0;

    while (timeAtSetPoint < .1)
    {
        updatePos(encoderL.read(), encoderR.read());
        error = angleDiff(getHeading(), finalAngle);

        currentTime = ((std::clock() - timer) / (double)CLOCKS_PER_SEC) + ((delayAmount / 1000.0) * numDelays);        
        double dt = currentTime - pastTime;

        double proportional = error / fabs(initialAngleDiff);
        integral += dt * ((error + pastError) / 2.0);
        double derivative = (error - pastError) / dt;

        double power = kp * proportional + ki * integral + kd * derivative;
        outputFile << "Error: " << error << "\tP: " << proportional * kp << "\tI: " << integral * ki << "\tD: " << derivative * kd << "\tpower: " << power << "\n";

        if (power > 0)
        {
            setMotorPowers(-power - f, power + f);
        }
        else
        {
            setMotorPowers(-power + f, power - f);
        }

        if (fabs(error) < .5)
        {
            if (!atSetpoint)
            {
                atSetpoint = true;
                firstTimeAtSetpoint = currentTime;
            }
            else //at setpoint
            {
                timeAtSetPoint = currentTime - firstTimeAtSetpoint;
            }
        }
        else //no longer at setpoint
        {
            atSetpoint = false;
            timeAtSetPoint = 0;
        }

        std::cout << "Error: " << error << "\tTAS: " << timeAtSetPoint << std::endl;

        pastTime = currentTime;
        pastError = error;
        delay(delayAmount);
        ++numDelays;
    }
    std::cout << "abs error: " << fabs(error) << std::endl;
    setMotorPowers(0, 0);
    outputFile.close();
}

void Robot::turnPixel(double finalPixel, double kp, double f, cv::Rect2d initialBB)
{
    startTracking(initialBB);
    delay(300);

    const double initialPixel = initialBB.x + initialBB.width / 2;
    const double initialPixelDiff = initialPixel - finalPixel;
    double error = initialPixelDiff;

    while (fabs(error) > 20)
    {
        updatePos(encoderL.read(), encoderR.read());
        error = getBallX() - finalPixel;

        //std::cout << "error: " << error;

        double y = getBallY();
        double proportional = error / fabs(initialPixelDiff);
        double power = proportional * kp * (y / 320.0);

        // std::cout << "\ty: " << y;
        // std::cout << "\tpower: " << power << std::endl;

        if (power > 0)
        {
            setMotorPowers(power + f, -power - f);
        }
        else
        {
            setMotorPowers(power - f, -power + f);
        }
    }
    std::cout << "EXITED LOOP" << std::endl;
    setMotorPowers(0, 0);
    stopTracking();
}

void Robot::curveToBall(cv::Rect2d initialBB, double power, double f) 
{
    startTracking(initialBB);
    startCollector();

    int initialBallCount = ballCount;
    double y = getBallY();
    while (initialBallCount == ballCount)
    {
        updatePos(encoderL.read(), encoderR.read());
        double currentX = getBallX();

        double leftProportion = currentX / getImageWidth();
        double rightProportion = 1 - leftProportion;

        y = getBallY();

        double heightFactor = 1 - (y / getImageHeight());

        double lPower = leftProportion * heightFactor * power;
        double rPower = rightProportion * heightFactor * power;

        setMotorPowers(lPower + f, rPower + f);
        std::cout << "count: " << ballCount << std::endl;
    }
    stopTracking();

    delay(500); //keep driving for 500ms in case there is a cluster
    setMotorPowers(0, 0);
    stopCollector();
}

void Robot::goToBall()
{
    startCamera();
    std::vector<cv::Rect2d> boxes = getBoundingBoxes();
    while (boxes.size() == 0) //while we don't see any balls
    {
        setMotorPowers(.2, -.2);
        boxes = getBoundingBoxes();
        delay(20);
    }
    setMotorPowers(0, 0);

    //now that we see a ball on the right of the screen, turn until it is at the left of the screen
    turnPixel(100, .5, .14, boxes.at(0));
    boxes = getBoundingBoxes();

    //find closest ball
    int minY = boxes.at(0).y;
    cv::Rect2d minBox = boxes.at(0);
    for (cv::Rect2d &box: boxes)
    {
        if (box.y < minY)
        {
            minY = box.y;
            minBox = box;
        }
    }

    turnPixel(500, .5, .14, minBox); //turn until it is dead center
    curveToBall(minBox, .5, .14);
}

void Robot::setMotorPowers(double lPower, double rPower)
{
    l.setPower(lPower);
    r.setPower(rPower);
    // printf( "\tlPower: %.3f", lPower);
    // printf("\trPower: %.3f", rPower);
    if (fabs(lPower) > 1 && fabs(rPower) > 1)
    {
        printf("\tTRIED TO SET POWER GREATER THAN 1\n");
    }
}