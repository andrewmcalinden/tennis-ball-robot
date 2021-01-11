#include<iostream>
#include "odometry.h"
#include "../math/mathUtil.h"
#include "../encoder/encoder.h"

int main()
{ 
    Encoder encoderL(7, 0);
    Encoder encoderR(2, 3);
    while (true)
    {
        updatePos(encoderL.read(), encoderR.read());
        printf("\rX: %.2f", getX());
        printf("   Y: %.2f", getY());
        printf("   Heading: %.2f", getHeading());
    }
}
