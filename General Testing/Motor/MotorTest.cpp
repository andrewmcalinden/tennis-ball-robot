#include "Motor.h"
#include <iostream>


#define directionPinForward 2
#define directionPinBackward 1
#define powerPin 23

int main(){
    Motor m(directionPinForward, directionPinBackward, powerPin);
    m.setPower(1);
    delay(2000);
    std::cout << "YEET2\n";
    m.setPower(.5);
    delay(2000);
    std::cout << "YEET1\n";
    m.setPower(.2);
    delay(2000);
    std::cout << "YEE3T\n";
}
