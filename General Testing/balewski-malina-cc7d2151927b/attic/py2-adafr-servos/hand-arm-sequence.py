#!/usr/bin/env python

"""
must be executed as sudo

operates to regular servos connected as arm and hand 
intends to move crawler form my AI class

"""

from Adafruit_PWM_Servo_Driver import PWM
import time
import RPi.GPIO as gpio

#=============================
#   MAIN 
#============================

# Initialise the PWM device using the default address
pwm = PWM(0x40, debug=False)

servoMin = 150  # Min pulse length out of 4096
servoMax = 600  # Max pulse length out of 4096


pwm.setPWMFreq(60)                        # Set frequency to 60 Hz
# assign pins on 16-servo controller
arm=1
hand=0

# assing buzzer to R-Pi pin
buzzPin=25

gpio.setmode(gpio.BCM) #Broadcom pin labelling
gpio.setup(buzzPin,gpio.OUT)

# test buzzer
delay=1
gpio.output(buzzPin,True)
time.sleep(delay)   
gpio.output(buzzPin,False)


for step in range(3):
  print "******** step=",step

  print "Reset Arm & hand to UP"
  pwm.setPWM(arm, 0, 300)
  time.sleep(delay)  
  pwm.setPWM(hand, 0, 400)
  time.sleep(delay)
  
  print " forward"
  pwm.setPWM(arm, 0, 220)
  time.sleep(delay)  
  gpio.output(buzzPin,True)
  pwm.setPWM(hand, 0, 380)
  time.sleep(delay)  
  gpio.output(buzzPin,False)

  print " touch"
  pwm.setPWM(arm, 0, 190)
  time.sleep(delay)  
  gpio.output(buzzPin,True)
  pwm.setPWM(hand, 0, 320)
  time.sleep(delay)  
  gpio.output(buzzPin,False)

  print " push"
  pwm.setPWM(arm, 0, 160)
  time.sleep(delay)  
  gpio.output(buzzPin,True)
  pwm.setPWM(hand, 0, 220)
  time.sleep(delay)  
  gpio.output(buzzPin,False)
  pwm.setPWM(arm, 0, 190)
  time.sleep(delay)  

  continue
  print "Reset Arm & hand to UP"
  pwm.setPWM(arm, 0, 270)
  time.sleep(delay) 
  pwm.setPWM(arm, 0, 300)
  time.sleep(delay) 
  pwm.setPWM(hand, 0, 400)
  time.sleep(delay)  
 
  

# important to cleanup afterwards
gpio.cleanup()
pwm.softwareReset()

