#include "../motor/motor.h"
#include "../encoder/encoder.h"
#include "turn.h"
#include <vector>
class Robot
{
    private:
    Motor l;
    Motor r;

    Encoder encoderL;
    Encoder encoderR;

    std::vector<Turn> turns;

    Vector startPos;

    unsigned char numMovements;
    unsigned char currentIndex;

    public:
    Robot(int lMotorDirPin, int lMotorPowerPin, int rMotorDirPin, int rMotorPowerPin,
            double initialX, double initialY, double initialTheta,
            int lEncoderPin1, int lEncoderPin2, int rEncoderPin1, int rEncoderPin2);

    void setMotorPowers(double lPower, double rPower);
    void run();

    void addMovement(Turn t);
};