/*
Author:  Jan Balewski,  September 2014

Measure time of operations with nano-sec precision

struct timespec {
  time_t   tv_sec; // since 1970
  long     tv_nsec;
}

*/


#include <stdio.h>
#include <stdlib.h>

#include <time.h> // for time measurement

//============================
int main (int argc, char *argv[]) {
  int nSamples=30;

  if (argc >1 ) nSamples =  atoi(argv[1]);

  printf( "#use: %s  nSamples=%d  \n", argv[0], nSamples);
  struct timespec tp1,tp2;  
 
    if ( clock_gettime( CLOCK_REALTIME, &tp1) == -1 ) {
      perror( "clock get time 1" );  return EXIT_FAILURE;
    }

    printf( "#Current time (since 1970) is %d sec %d nsec \n",tp1.tv_sec, tp1.tv_nsec);

    if ( clock_gettime( CLOCK_REALTIME, &tp2) == -1 ) {
      perror( "clock get time 2" );  return EXIT_FAILURE;
    }

    printf( "#Printing last line took %d sec %d nsec or %d usec \n",tp2.tv_sec-tp1.tv_sec,tp2.tv_nsec- tp1.tv_nsec,(tp2.tv_nsec- tp1.tv_nsec)/1000);

  
    int nd;
    double tRel;
    for (nd=0; nd<nSamples; nd++)  {

      if ( clock_gettime( CLOCK_REALTIME, &tp2) == -1 ) {
	perror( "clock get time 2" );  return EXIT_FAILURE;
      }

      // this way assures fractional seconds are accounted properly
      tRel=tp2.tv_sec-tp1.tv_sec; // units are sec
      tRel+=(tp2.tv_nsec- tp1.tv_nsec)*1.e-9; // units were in nsec
      printf("nd=%d tRel=%.6f (sec)\n",nd,tRel);
      
      usleep(300*1000); // this is 0.3 seconds
    }


    printf("\n --- end of test \n");
	return 0 ;
}
