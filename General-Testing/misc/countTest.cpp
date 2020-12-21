#include "wiringPi.h"

#define COLLECTOR_PIN 4
#define COUNT_INPUT_PIN 12

using namespace std;

volatile int count = 0;
volatile int oldCount = 0;

void countUp(){
    oldCount = count;
    count++;    
}

int main()
{   digitalWrite(COLLECTOR_PIN, HIGH);
    wiringPiISR (COUNT_INPUT_PIN, INT_EDGE_FALLING, &countUp);
    
    while(true){
        if (count > oldCount){
            printf("\r",count);
            oldCount = count;
            }
    }
}