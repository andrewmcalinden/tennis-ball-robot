#!/usr/bin/env python

# Simple demo of of the PCA9685 PWM servo/LED controller library.
# This will move channel 0 from min to max position repeatedly.
# Author: Tony DiCola
# License: Public Domain
# modified: Jan Balewski , Nevember 2016
# change: runs as non-sudo using pigpiod deamon
"""
To check I2C address  for servo-16 is 0x40:

(on Raspberry Pi B+ type)
sudo i2cdetect -y 1
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
...
30: -- -- -- -- -- -- -- -- -- -- -- UU -- -- -- --
40: 40 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
...
"""

from __future__ import division
import time

import sys,os
sys.path.append('/home/balewski/malina/common/')
from rpiUtils import *
import rospy

# Import the PCA9685 module.
sys.path.append('/home/balewski/Adafruit_Python_PCA9685/Adafruit_PCA9685')
import  PCA9685 as Adafruit_PCA9685

# Uncomment to enable debug output.
import logging
logging.basicConfig(level=logging.DEBUG)

# Connect to R-Pi daemon
isRPi(rospy)
rpiDrv = getGPIO(rospy)
dumpPIGIOver(rpiDrv)

# this test requires an PCA9685 on I2C bus 1 addr 0x40
''' 
To check I2C address  for servo-16 is 0x40:
sudo i2cdetect -y 1
'''
i2cDrv=i2c_ala_adafruit(rpiDrv)

# Initialise the PCA9685 using the default address (0x40).
pwm = Adafruit_PCA9685.PCA9685(i2c=i2cDrv)

# Configure min and max servo pulse lengths
servo_min = 160  # Min pulse length out of 4096
servo_max = 590  # Max pulse length out of 4096

# Helper function to make setting a servo pulse width simpler.
def set_servo_pulse(channel, pulse):
    pulse_length = 1000000    # 1,000,000 us per second
    pulse_length //= 60       # 60 Hz
    print('{0}us per period'.format(pulse_length))
    pulse_length //= 4096     # 12 bits of resolution
    print('{0}us per bit'.format(pulse_length))
    pulse *= 1000
    pulse //= pulse_length
    pwm.set_pwm(channel, 0, pulse)

# Set frequency to 60hz, good for servos.
pwm.set_pwm_freq(60)

print('Moving servo on channel 0, press Ctrl-C to quit...')

k=0
while k<2:
    # Move servo on channel O between extremes.
    pwm.set_pwm(0, 0, servo_min)
    time.sleep(1)
    pwm.set_pwm(0, 0, servo_max)
    time.sleep(1)
    k+=1

print('stop all servos')
"""Sends a software reset (SWRST) command to all servo drivers on the bus."""
i2cDrv.softwareReset()
i2cDrv.close()
rpiDrv.stop()
print('end-jan')
