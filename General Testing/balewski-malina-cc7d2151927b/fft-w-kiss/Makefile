
KISS_FFT_BASE=/usr/local/kiss_fft/

WARNINGS=-W -Wall -Wstrict-prototypes -Wmissing-prototypes -Waggregate-return \
    -Wcast-qual -Wnested-externs -Wshadow -Wbad-function-cast \
    -Wwrite-strings
#jan: -Wcast-align 

CFLAGS=-O3 -I.. -I$(KISS_FFT_BASE)  -I$(KISS_FFT_BASE)/tools  $(WARNINGS)
CFLAGS+=-ffast-math -fomit-frame-pointer 
CFLAGS+= $(CFLAGADD)


ifeq "$(DATATYPE)" ""
 DATATYPE=float
endif


TESTREAL=tr_$(DATATYPE)

TYPEFLAGS=-Dkiss_fft_scalar=$(DATATYPE)

ifeq  "$(DATATYPE)" "int16_t" 
 TYPEFLAGS=-DFIXED_POINT=16
endif


ifeq  "$(DATATYPE)" "float"
 # fftw needs to be built with --enable-float to build this lib
 #FFTWLIB=-lfftw3f
else
 #FFTWLIB=-lfftw3
endif

#FFTWLIBDIR=-L/usr/local/lib/

SRCFILES= $(KISS_FFT_BASE)/kiss_fft.c $(KISS_FFT_BASE)/tools/kiss_fftnd.c  $(KISS_FFT_BASE)/tools/kiss_fftr.c  $(KISS_FFT_BASE)/tools/kfc.c $(KISS_FFT_BASE)/tools/kiss_fftndr.c

all:    $(TESTREAL) brain1_fft


$(TESTREAL): test_realFFT.c $(SRCFILES)
	$(CC) -o $@ $(CFLAGS) $(TYPEFLAGS) $+ -lm
	@echo "\n done, exec:    ./$@ \n"

brain1_fft:  brain1_fft.c  $(SRCFILES)
	$(CC) -o $@ $(CFLAGS) $(TYPEFLAGS) $+ -lm
	@echo "\n done, exec:    ./$@ \n"

clean:
	rm -f tr_float brain1_fft
