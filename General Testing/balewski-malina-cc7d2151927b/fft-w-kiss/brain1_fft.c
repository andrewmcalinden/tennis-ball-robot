// Author: Jan Balewski, October, 2014
/* Preform just one FFT on the real data of arbitrary size (run time param), 
   print amplitudes of all frequencies, assume hardcoded sampFreq (Hz) of # of input data per second
   Based on very simplified 'test/test_real.c' .
*/
 
#include "kiss_fftr.h"
#include "_kiss_fft_guts.h"
#include <sys/times.h>
#include <time.h>
#include <unistd.h>

/* enum {ND=10};
int adcA[ND] ={ 1,2,3,2,1,0,1,2,3,2}; 
*/

//......data take 10-18-2014
#include "rawHuman1.h"


//........ data taken 10-17-2014
//#include "sin15hz.h" 

int main(int argc,char ** argv) {
  int i;
  if (argc>1)   i=atoi(argv[1]); // to make compiler happy

    int size = ND;
    if(size%2) size--; // kissFFT wants only even number of data

   
 
    // Needed only for interpreting the results
    float scaling=1.0/(float)size;

    // Provide sampling frequency (in Hz)
    float sampFreq=1./sampPeriod; // (Hz) number of data points per second
    printf("main: data sample size=%d,  sampling freq=%.1f (Hz)\n",size,sampFreq);


    // Variables essential for FFT calculation
    kiss_fft_scalar rin[size+2]; // real input vector: INPUT
    kiss_fft_cpx cout[size]; // complex OUTPUT vector
    kiss_fftr_cfg  kiss_fftr_state = kiss_fftr_alloc(size,0,0,0);
    kiss_fft_scalar zero; // not essetnial - I keep it here as example for comples input
    memset(&zero,0,sizeof(zero) ); // ugly way of setting short,int,float,double, or __m128 to zero
  

    //---- copy input data to the kiss-container
  
    for (i=0;i<size;++i) {
      rin[i] = adcA[i];
    }  
 
  
   clock_t start_t, stop_t; // allocate them before use to not obsucre timing measurement
    start_t = clock();
    //   kiss_fft(kiss_fft_state,cin,cout);
    kiss_fftr(kiss_fftr_state,rin,cout);
    stop_t = clock();
    double total_t = (double)(stop_t - start_t) / CLOCKS_PER_SEC;
    printf("done FFT of %d channels took %.2e sec \n",size,total_t);
    printf("freq(Hz), FFT ampl, FFT phase(rad)\n");
    for (i=0;i<size;++i) {
      // a) the real and imaginary components of the output need to be combined to calculate the amplitude at each frequency. 
      double ar=cout[i].r;
      double ai=cout[i].i; 
      // then for each output [i] from the FFT...
      double  ampl = 2.0 * sqrtf( ar*ar + ai*ai ) * scaling ;
   
      // b) which index refers to which frequency? This can be calculated as follows. Only the first half of the FFT results are needed (assuming your sampFreq  sampling rate) 
      double freq = (float)i / (1/sampFreq) / (float)size ; 
      
      // c)  phase (range +/- PI) for each frequency is calculated like this:       
      double phase = atan2(ai , ar); // [rad]

      /*  Note: frequency-domain data is stored from dc up to 2pi.
	  so cx_out[0] is the dc bin of the FFT
	  and cx_out[nfft/2] is the Nyquist bin (if exists) */
      if(i==0) ampl/=2; // un-do 2x for DC amplitude
      if (i>=size/2) { freq=0; ampl=0; phase=0; break;}

      //char X=' ';
      //if(ampl>0.1) X='*'; // tag large amplitudes

      // full dump
      // printf("bin=%d  inp=%.3f    out: freq=%.1fHz  %c ampl=%.1f  phase=%.3f/rad\n",i,rin[i],freq,X,ampl,phase);

      //CSV just freq, ampl, phase
      if(i)printf("%.1f,  %.1f,   %.3f\n", freq,ampl,phase);

      //      if(i>30 ) { printf("skip too many printouts ...\n"); break;}
      if(freq>40 ) { printf("skip too high frequencies ...\n"); break;}
    }
    
    printf("jan: END\n");
    return 0; 
}
