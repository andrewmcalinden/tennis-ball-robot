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
  startReading(); // spawns the threads in the
  //enableBuffering(); // disabled by default

  // disable output buffering to stdout
  setvbuf(stdout, NULL, _IONBF, 0);

  printf("%d\n", value);
  while( 1 )
  {
    char reading = getReading();
    printf("\n%d\n", (int) reading);
    /* ["critical section"]
     * Do whatever you like with the reading here
     * For now we are just printing a knob value.
     * Clockwise - is positive, increments the value
     * Counterclockwise - decrements the value
     * Pressing knob  - resets the value to 0 
     * If buffering is enabled, any activity will be
     * read into a buffer (until full) while in this
     * critical section. If buffering is not enabled
     * then all values being read in while in this 
     * critical section are ignored, until the call
     * to continueReading().
     */
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
    printf("dog\n");
    /* ["critical section end"] */

    continueReading(); 
  }

  return 0;
}
