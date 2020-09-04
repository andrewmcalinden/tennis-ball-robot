#!/usr/bin/env python

""" 

must be executed as sudo

"""
from time import sleep
import RPi.GPIO as GPIO

# using BCM GPIO 00..nn numbers
GPIO.setmode(GPIO.BCM)

pinIn=21
pinOut=12
print "pinIn=",pinIn,"  pinOut=",pinOut

# Set up the GPIO channels - one input and one output
GPIO.setup(pinIn, GPIO.IN)
GPIO.setup(pinOut, GPIO.OUT)

# Input from pin 11
input_value = GPIO.input(pinIn)
print "inp on pinIn=",input_value

for i in range(0,5):
    print i, "set high"
    # Output to pin-out
    GPIO.output(pinOut, GPIO.HIGH)
    sleep(1)
    print  "  set low"
    # Output to pin 5
    GPIO.output(pinOut, GPIO.LOW)
    sleep(1)

# important to cleanup afterwards
GPIO.cleanup() 
