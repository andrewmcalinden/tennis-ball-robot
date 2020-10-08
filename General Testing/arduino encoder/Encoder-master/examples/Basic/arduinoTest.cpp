/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>


//   avoid using pins with LEDs attached

int main()
{
    //   Change these two numbers to the pins connected to your encoder.
    //   Best Performance: both pins have interrupt capability
    //   Good Performance: only the first pin has interrupt capability
    //   Low Performance:  neither pin has interrupt capability
    Encoder myEnc(5, 6);
    long oldPosition = -999;
    while (true)
    {
      long newPosition = myEnc.read();
      if (newPosition != oldPosition)
      {
        oldPosition = newPosition;
        std::cout << newPosition;
      }
    }
}
