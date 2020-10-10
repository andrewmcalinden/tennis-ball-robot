#ifndef ENCODER_H
#define ENCODER_H

#include <stdbool.h>

/**
 * C API for interfacing a Bourns Pro Audio Incremental Encoder
 * (PEC11-4215F-S24) with a Rasberry Pi
 * https://github.com/comychitz/encoder
 */

#define NO_ACTION 	       ( (const char) 0x00 )
#define CLOCKWISE_STEP	       ( (const char) 0x01 )
#define COUNTER_CLOCKWISE_STEP ( (const char) 0x02 )
#define PUSHED		       ( (const char) 0x03 )
#define PUSHED_AND_HELD	       ( (const char) 0x04 )

bool setup( int pinA, int pinB, int pinC );

void clearBuffer( void );

bool enableBuffering( void );

bool disableBuffering( void );

void setHoldTime( long long holdTime );

bool startReading( void );

void stopReading( void );

char getReading( void );

void continueReading( void );

#endif /* ENCODER_H */
