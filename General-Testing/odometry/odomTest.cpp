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
        // std::cout << "\nX:";
        // printf("%.2f", getX());
        // std::cout << "  Y:";
        // printf("%.2f", getY());
        // std::cout << "  Heading:";
        // printf("%.2f", getHeading());
        std::cout << "\r        ";
        std::cout << "\rX:" << getX();        
    }
}
