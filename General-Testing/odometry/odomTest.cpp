#include<iostream>
#include "odometry.h"
#include "../encoder/encoder.h"

int main()
{ 
    Encoder encoderL(7, 0);
    Encoder encoderR(2, 3);
    while (true)
    {
/*
-y
-x  +x
+y
*/        updatePos(encoderL.read(), encoderR.read());
        printf("\rX: %.2f", globalXPos);
        printf("   Y: %.2f", globalYPos);
        printf("   Heading: %.2f", globalHeading);
    }
}
