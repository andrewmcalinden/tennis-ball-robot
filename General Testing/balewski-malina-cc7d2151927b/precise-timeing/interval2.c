/*
Author:  Jan Balewski,  September 2014

Measure time of operations with nano-sec precision
This versin compiles on Mac Os 10.9.5

Manual compilation:
cc interval2.c -o interval2   -L/usr/local/lib 

It does not work well on R-Pi, got resoulton of 0.01 sec

Based on:
http://www.tutorialspoint.com/c_standard_library/c_function_clock.htm

     The clock() function determines the amount of processor time used since
     the invocation of the calling process, measured in CLOCKS_PER_SECs of a
     second.

*/


#include <stdio.h>
#include <stdlib.h>

#include <time.h> // for time measurement
#include <unistd.h> // for usleep()
#include <math.h> // for trig unctions

//--------------------------------------
/* here do some computation, 
   n=1 takes about  0.9 usec on Mac PowerBok Pro
   make sure to not exceed max_int (keep n<100k)
*/
void hardTask(int n) {
   int i;
  for(i=0; i< n*10000; i++)   {
    double x=sin(i), y=cos(x), z= pow(x,2.34)+sqrt(x*y);
  }
}


//--------------------------------------
int main (int argc, char *argv[]) {
  int nSamples=300;

  if (argc >1 ) nSamples =  atoi(argv[1]);

  printf( "#use: %s  nSamples=%d  \n", argv[0], nSamples);

  clock_t start_t, end_t; // allocate them before use to not obsucre timing measurement
  printf(" CPU clock speed pulses/sec is %d\n",CLOCKS_PER_SEC);
  printf("Step 1: calibrate your computer with  big loop, nSamples=%d\n",  nSamples);
  start_t = clock();
  hardTask(nSamples);
  end_t = clock();
  printf("End of the big loop, start_t=%ld, end_t = %ld\n",start_t, end_t);
  if(end_t==-1){ // you do not need to check for error each time - this is an overkill
    perror( "clock get time 2" );  return EXIT_FAILURE;
  }
  double total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
  printf("Total time taken by CPU: %f (sec)\n", total_t  );
  
   // test 2
   printf("\nStep 2, exactly measure  ~1.8 mSec worth of computation\n");
   start_t = clock();
   hardTask(2);
   end_t = clock();
   total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
   printf("Short job time: %.1f (uSec)\n", total_t*1e6  );

   printf("Exiting of the program...\n");

   return(0);
}

