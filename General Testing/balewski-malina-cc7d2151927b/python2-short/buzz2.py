#!/usr/bin/env python

"""
must be executed as sudo

Connections:
piezzo: ground+pin

"""


import RPi.GPIO as gpio
import time                          #import the time library

print 'start1'
gpio.setmode(gpio.BCM) #Broadcom pin labelling

buzzPin=25

gpio.setup(buzzPin,gpio.OUT)
print 'start2'

def buzz(pitch, duration):
    print "pitch=",pitch
    period = 1.0 / pitch     #the period (sec/cyc) is the inverse of the frequency (cyc/sec)
    delay = period / 2     #calcuate the time for half of the wave
    cycles = int(duration * pitch)   #the number of waves to produce is the duration times the frequency

    for i in range(cycles):    #start a loop from 0 to the variable cycles calculated above

        gpio.output(buzzPin, True)   #set pin 18 to high        
        time.sleep(delay)    #wait with pin 18 high
        gpio.output(buzzPin, False)    #set pin 18 to low        
        time.sleep(delay)    #wait with pin 18 low


#----- M A I N -----
print 'start2'
len=3
freq=400
print 'freq=',freq
buzz(freq,len)

# important to cleanup afterwards
#gpio.cleanup() ;exit()

freq=800
print 'freq=',freq
buzz(freq,len)

freq=1200
print 'freq=',freq
buzz(freq,len)

freq=1600
print 'freq=',freq
buzz(freq,len)


# important to cleanup afterwards
gpio.cleanup()

