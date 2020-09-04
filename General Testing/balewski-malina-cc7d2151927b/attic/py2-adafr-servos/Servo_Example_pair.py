#!/usr/bin/env python

"""
must be executed as sudo

rotate servo connected to chan=0 
sudo i2cdetect -y 1

"""

from Adafruit_PWM_Servo_Driver import PWM
import time


# Initialise the PWM device using the default address

pwm = PWM(0x40, debug=False)

#servoMin = 180  # Min pulse length out of 4096
#servoMax = 550  # Max pulse length out of 4096
servoMin=250; servoMax=560

#=============================
#   MAIN 
#============================

pwm.setPWMFreq(60)                        # Set frequency to 60 Hz
k=0
delT=0.2
while (True and k<18):
  # Change speed of continuous servo on channel O
  pwm.setPWM(0, 0, servoMin)
  time.sleep(delT)
  pwm.setPWM(1, 0, servoMin)
  time.sleep(delT)
  #break

  pwm.setPWM(0, 0, servoMax)
  time.sleep(delT)
  pwm.setPWM(1, 0, servoMax)
  time.sleep(delT)

  k+=1

  #break

pwm.softwareReset()


