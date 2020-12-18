#include "../motor/motor.h"
#include "../encoder/encoder.h"
#include "movement.h"
#include "experimentalTurn.h"
#include "experimentalLine.h"
#include <vector>
class ExperimentalRobot
{
    private:
    Motor l;
    Motor r;

    Encoder encoderL;
    Encoder encoderR;

    std::vector<Movement> movements;

    unsigned char numMovements;
    unsigned char currentIndex;

    public:
    ExperimentalRobot(int lMotorDirPin, int lMotorPowerPin, int rMotorDirPin, int rMotorPowerPin,
                        double initialX, double initialY, double initialTheta,
                        int lEncoderPin1, int lEncoderPin2, int rEncoderPin1, int rEncoderPin2);

    void setMotorPowers(double lPower, double rPower);
    void run();

    void addMovement(Movement m);
};