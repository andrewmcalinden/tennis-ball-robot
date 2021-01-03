#include<iostream>
#include "odometry.h"
#include "../encoder/encoder.h"

int main()
{ 
    Encoder encoderL(0, 7);
    Encoder encoderR(3, 2);
    while (true)
    {
        std::cout << "\rleft: " << encoderL.read() << "\tright: " << encoderR.read();
        updatePos(encoderL.read(), encoderR.read());
        // printf("\rX: %.2f", globalXPos);
        // printf("   Y: %.2f", globalYPos);
        // printf("   Heading: %.2f", globalHeading);
    }
}
