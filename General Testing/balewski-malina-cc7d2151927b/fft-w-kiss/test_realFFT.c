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

int main(int argc,char ** argv) {
    int size = 64;
    int i;
    if (argc>1)   
        size = atoi(argv[1]);
    printf("main: data sample size=%d\n",size);

    // Needed only for interpreting the results
    float scaling=1.0/(float)size;

    // Provide sampling frequency (in Hz)
    float sampFreq=32; // (Hz) number of data points per second

    // Variables essential for FFT calculation
    kiss_fft_scalar rin[size+2]; // real input vector: INPUT
    kiss_fft_cpx cout[size]; // complex OUTPUT vector
    kiss_fftr_cfg  kiss_fftr_state; // not sure what for is this one 
    kiss_fft_scalar zero; // not essetnial - I keep it here as example for comples input
    memset(&zero,0,sizeof(zero) ); // ugly way of setting short,int,float,double, or __m128 to zero
    kiss_fftr_state = kiss_fftr_alloc(size,0,0,0);

    //----  prpare fake data: 2 harmonics and  DC offset
    double omega1=3.1416/8; // period=12 bins
    double omega2=3*omega1;
    double dcAmpl=-2.2;

    for (i=0;i<size;++i) {
      rin[i] = dcAmpl+ 0.9*cos(omega1*i) -  0.4*cos(omega2*i);
      // cin[i].r = rin[i]; // in case you want complex input with only non-zero real component
      // cin[i].i = zero;
    }  
 
  
   clock_t start_t, stop_t; // allocate them before use to not obsucre timing measurement
    start_t = clock();
    //   kiss_fft(kiss_fft_state,cin,cout);
    kiss_fftr(kiss_fftr_state,rin,cout);
    stop_t = clock();
    double total_t = (double)(stop_t - start_t) / CLOCKS_PER_SEC;
    printf("done FFT of %d channels took %e sec \n",size,total_t);
  
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

      char X=' ';
      if(ampl>0.1) X='*'; // tag large amplitudes

      printf("bin=%d  inp=%.3f    out: freq=%.1fHz  %c ampl=%.1f  phase=%.3f/rad\n",i,rin[i],freq,X,ampl,phase);

      if(i>30 ) { printf("skip too many printouts ...\n"); break;}
    }
    
    printf("jan: END\n");
    return 0; 
}
