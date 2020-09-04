#!/usr/bin/python
from Adafruit_MotorHAT import Adafruit_MotorHAT, Adafruit_DCMotor

import time
import atexit

# create a default object, no changes to I2C address or frequency
mh = Adafruit_MotorHAT(addr=0x60)

# recommended for auto-disabling motors on shutdown!
def turnOffMotors():
	mh.getMotor(1).run(Adafruit_MotorHAT.RELEASE)
	mh.getMotor(2).run(Adafruit_MotorHAT.RELEASE)
	mh.getMotor(3).run(Adafruit_MotorHAT.RELEASE)
	mh.getMotor(4).run(Adafruit_MotorHAT.RELEASE)

atexit.register(turnOffMotors)

################################# DC motor test!
myMotor = mh.getMotor(1)

# set the speed to start, from 0 (off) to 255 (max speed)
myMotor.setSpeed(150)
myMotor.run(Adafruit_MotorHAT.FORWARD);
# turn on motor
myMotor.run(Adafruit_MotorHAT.RELEASE);

mxSpeed=180
D=0.01
while (True):
	print "Forward! "
	myMotor.run(Adafruit_MotorHAT.FORWARD)

	print "\tSpeed up..."
	for i in range(mxSpeed):
		myMotor.setSpeed(i)
		if i%10==0:
			print i,
		time.sleep(D)

	print "\tSlow down..."
	for i in reversed(range(mxSpeed)):
		myMotor.setSpeed(i)
		if i%10==0:
			print i,
		time.sleep(D)

	print "Backward! "
	myMotor.run(Adafruit_MotorHAT.BACKWARD)

	print "\tSpeed up..."
	for i in range(mxSpeed):
		myMotor.setSpeed(i)
		time.sleep(D)

	print "\tSlow down..."
	for i in reversed(range(mxSpeed)):
		myMotor.setSpeed(i)
		time.sleep(D)

	print "Release"
	myMotor.run(Adafruit_MotorHAT.RELEASE)
	time.sleep(1.0)
