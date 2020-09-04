#!/usr/bin/env python

"""
must be executed as sudo

Connections:
piezzo: ground+pin
LED: ground+pin
"""


import RPi.GPIO as gpio
gpio.setmode(gpio.BCM) #Broadcom pin labelling

buzzPin=25
ledPin=4
gpio.setup(buzzPin,gpio.OUT)
gpio.setup(ledPin,gpio.OUT)


def delay(j):
 for k in range(1,j):     
     pass

def fire():
 for j in range(1,1100):
  gpio.output(buzzPin,True)
  delay(j)
  gpio.output(buzzPin,False)
  delay(j)


#----- M A I N -----
gpio.output(ledPin,True)
fire()
gpio.output(ledPin,False)

# important to cleanup afterwards
gpio.cleanup()

