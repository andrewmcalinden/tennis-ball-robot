#include<iostream>
#include "odometry.h"
#include "../encoder/encoder.h"
using namespace std;

int main()
{ 
    Encoder encoderL(0, 7);
    Encoder encoderR(2, 3);
    string out ="";
    while (true)
    {
        updatePos(encoderL.read(), encoderR.read());
        out += "\rX:","%.2f",getX(),"  Y:","%.2f",getY(),"  Heading:","%.2f", getHeading();
        
        
        printf(out.c_str());        
    }
}
