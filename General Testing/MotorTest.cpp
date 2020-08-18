#include<Motor.h>

#define directionPinForward 0
#define directionPinBackward 0
#define powerPin 0

int main(){
    Motor m(directionPinForward, directionPinBackward, powerPin);
    m.setPower(1);
    delay(2000);
    m.setPower(.5);
    delay(2000);
    m.setPower(0);
    delay(2000);
}