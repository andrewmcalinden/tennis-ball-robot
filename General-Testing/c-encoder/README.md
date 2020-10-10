## encoder
A small set of C functions targeted for iterfacing a rotary encoder (specifically, Bourns Pro Audio Incremental Encoder PEC11-4215F-S24) with a Raspberry Pi B+ V1.2.

### usage
Include "encoder.h" in your C/C++ program and link with the encoder object file. 

defined event types:
  - CLOCKWISE_STEP
  - COUNTER_CLOCKWISE_STEP
  - PUSHED
  - PUSHED_AND_HELD

to set the gpio pins to read the data from the encoder on the pi use the integer globals PIN_A, PIN_B, PIN_C. see the image here (https://github.com/comychitz/encoder/blob/master/encoder_gpio_pin_out.png) for the pin out.

##### dependencies
1. wiringPi 
2. pthread

### simple example
```C
/**
 * A simple meter with no limits
 * Turning the encoder clockwise increases the value, 
 * counter-clockwise decreases it. If you press, it 
 * will reset to 0. If you press an hold, it will set 
 * the value to 100.
 */
#include "encoder.h"
#include <stdio.h>

// the gpio pins to use
int gpioA = 7,
    gpioB = 0,
    gpioC = 2;

int main( )
{
  int value = 0;

  setup( gpioA, gpioB, gpioC );    
  startReading();

  while( 1 ) 
  {
    char reading = getReading();

    /* ["critical section start"] */
    if( reading == CLOCKWISE_STEP )
    {
      value++;
    }   
    else if( reading == COUNTER_CLOCKWISE_STEP )
    {
      value--;
    }   
    else if( reading == PUSHED )
    {
      value = 0;
    } 
    else if( reading == PUSHED_AND_HELD )
    {
      value = 100;
    }
    printf( "%d\n", value );
    /* ["critical section end"] */

    continueReading(); 
  }

  stopReading();

  return 0;
}
```
