#include "encoder.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE	      256

// globals
pthread_t rotateThread, pushThread;
bool bufferingEnabled;
sem_t produced, consumed;
pthread_mutex_t bufferLock;

void add_to_buffer( char value );
void monitorRotation( void * );
void monitorPushButton( void * );
bool getPushButtonReading( void );
char getKnobReading( char prev );

int RUNNING = 0;
char buffer[BUFFER_SIZE];
int START = -1, END = 0;
long long HOLD_TIME = 2000; // in milliseconds
bool isSetup = false;

bool setup( int pinA, int pinB, int pinC ) 
{
  wiringPiSetup(); // will abort the program if fails in here
  pinMode( pinA, INPUT );
  pullUpDnControl( pinA, PUD_UP );
  pinMode( pinB, INPUT );
  pullUpDnControl( pinB, PUD_UP );
  pinMode( pinC, INPUT );
  pullUpDnControl( pinC, PUD_UP );
  bufferingEnabled = false;

  // TODO - add checks for these init functions below
  sem_init( &produced, 0, 0 );
  sem_init( &consumed, 0, 0 );
  pthread_mutex_init( &bufferLock, NULL );

  isSetup = true;
  return true;
}

void clearBuffer( void )
{
  START = -1;
  END = 0;
  //sem_post(&consumed); TODO - is this right?
}

bool enableBuffering( void )
{
  clearBuffer();
  bufferingEnabled = true;
  return true;
}

bool disableBuffering( void )
{
  clearBuffer();
  bufferingEnabled = false;
  return true;
}

void setHoldTime( long long holdTime )
{ // function to set the time (in milliseconds) of distinguishing between
  // a button press and a button hold
  HOLD_TIME = holdTime;
}

bool startReading( void )
{
  // TODO - spawn threads in a joinable state? is that necessary?
  if( !isSetup )
  {
    fprintf( stderr, "Called startReading() without a successful setup (did you forget to call setup()?)" );
    exit(-1);
  }
  if( !RUNNING )
  { // start threads for the rotation and push button 
    if( pthread_create( &rotateThread, NULL, ( void* ) &monitorRotation, NULL ) != 0 )
    {
      fprintf( stderr, "Failed to create monitor rotation thread!\n" );
      return false;
    }
    if( pthread_create( &pushThread, NULL, ( void* ) &monitorPushButton, NULL ) != 0 )
    {
      fprintf( stderr, "Failed to create monitor push button thread!\n" );
      return false;
    }
    RUNNING = 1;
  }
  else
  {
    fprintf( stderr, "Call to startReading() when threads are already running!\n" );
  }
  return true;
}

void stopReading( void )
{
  if( RUNNING == 0 )
  {
    if( pthread_cancel( rotateThread ) != 0 )
    {
      fprintf( stderr, "Failed to stop monitor rotation thread!\n" );
    }
    if( pthread_cancel( pushThread ) != 0 )
    {
      fprintf( stderr, "Failed to stop monitor push button thread!\n" );
    }
    RUNNING = 0;
  }
  else
  {
    fprintf( stderr, "Call to stopReading when threads are already stopped!\n" );
  }
}

char getReading( void )
{
  if( !isSetup )
  {
    fprintf( stderr, "Called getReading() without a successful setup (did you forget to call setup()?)" );
    exit(-1);
  }
  if( !RUNNING )
  {
    fprintf( stderr, "Called getReading() without a successful startReading() call. Exiting..." );
  }
  sem_wait(&produced);
  char value = buffer[START];
  START = (START+1) % BUFFER_SIZE;
  return value;
}

void continueReading( void )
{
  if( RUNNING )
  {
    sem_post(&consumed);
  }
}

void add_to_buffer( char value )
{
  pthread_mutex_lock(&bufferLock);
  if( START == END )
  {
    sem_wait(&consumed);
  }
  if( START == -1 )
  {
    START++;
  }
  buffer[END] = value;
  END = ( END + 1 ) % BUFFER_SIZE;

  sem_post( &produced );

  if( !bufferingEnabled )
  {
    sem_wait(&consumed);
    clearBuffer();
  }
  pthread_mutex_unlock(&bufferLock);
}

void monitorRotation( void *input )
{
  while(1) 
  {
    char reading1 = getKnobReading( 0x00 );
    if( reading1 != 0x00 )
    {
      char reading2 = getKnobReading( reading1 );
      if( reading2 == 0x03 )
      {
	char reading3 = getKnobReading( reading2 );
	if( 2 == reading2 - reading3 && reading1 == 2 )
	{
	  add_to_buffer( CLOCKWISE_STEP );
	} 
	else
	{
	  add_to_buffer( COUNTER_CLOCKWISE_STEP );
	}
      }
    }
  }
}

void monitorPushButton( void * input )
{
  int timeHeldDown = 0;
  while(1)
  {
    if( getPushButtonReading() )
    {
      add_to_buffer( PUSHED );
      timeHeldDown = 0;
      while( getPushButtonReading() )
      {
	timeHeldDown += 1;
	if( timeHeldDown >= HOLD_TIME * 2000 )
	{ 
	  add_to_buffer( PUSHED_AND_HELD );
	  break;
	}
      }
      while( getPushButtonReading() )
      {
	// wait for it to be released
      }
    }
    usleep( 1000 * 10 ); // 10 millisecond sleep
  }
}

char getKnobReading( char prev )
{
  char state;

  do {
    int A = digitalRead( 7 );
    int B = digitalRead( 0 );
    state = 0x00;

    if( A == 0 ) 
    {
      state |= 0x02;
    }
    else
    {
      state &= 0x01;
    }
    if( B == 0 )
    {
      state |= 0x01;
    }
    else
    {
      state &= 0x02;
    }

    usleep( 1000 ); // 10 millisecond sleep
  } while( prev == state );

  return state;
}

bool getPushButtonReading( void )
{
  // returns true when pressed, otherwise false
  if( !digitalRead( 2 ) )
  {
    return true;
  }
  return false;
}
