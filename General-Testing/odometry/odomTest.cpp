#include<iostream>
#include "odometry.h"
#include "../encoder/encoder.h"

int main()
{ 
    Encoder encoderL(0, 7);
    Encoder encoderR(2, 3);
    while (true)
    {
        updatePos(encoderL.read(), encoderR.read());
        printf("\rX: %.2f",getX());
        printf("   Y: %.2f",getY());
        printf("   Heading: %.2f",getHeading());
    }
}
