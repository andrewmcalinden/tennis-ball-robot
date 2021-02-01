from __future__ import print_function
import RPi.GPIO as GPIO
import xbox
import time

rPowerPin = 12
rDirPin = 16
lPowerPin = 13
lDirPin = 6
collectPin = 23
countPin = 10

GPIO.setmode(GPIO.BCM)

GPIO.setup(rPowerPin, GPIO.OUT)
GPIO.setup(rDirPin, GPIO.OUT)
GPIO.setup(lPowerPin, GPIO.OUT)
GPIO.setup(lDirPin, GPIO.OUT)
GPIO.setup(collectPin, GPIO.OUT)
#GPIO.setup(countPin, GPIO.IN)

rightPwn = GPIO.PWM(rPowerPin, 5000)
leftPwn = GPIO.PWM(lPowerPin, 5000)
rightPwn.start(0)
leftPwn.start(0)



# Format floating point number to string format -x.xxx
def fmtFloat(n):
    return '{:6.3f}'.format(n)

def setRightPower(power):
    rightPwn.ChangeDutyCycle(99*abs(power))
    if power >= 0:
       GPIO.output(rDirPin, GPIO.HIGH)
    else:
        GPIO.output(rDirPin,GPIO.LOW)

def setLeftPower(power):
    leftPwn.ChangeDutyCycle(99*abs(power))
    if power >= 0:
       GPIO.output(lDirPin, GPIO.HIGH)
    else:
        GPIO.output(lDirPin,GPIO.LOW)


collectOn = False
ballCount = 0

# Instantiate the controller
joy = xbox.Joystick()

# Show various axis and button states until Back button is pressed
print("Xbox controller sample: Press Back button to exit")
while not joy.Back():

    power = joy.rightTrigger()-joy.leftTrigger()
    #if (joy.leftX()>0 and joy.leftX()<.75):
        

    if ((1-joy.leftX())*power)>1:
        rightPower = 1
    else:
        rightPower = (1-(joy.leftX())*power)
    
    if ((1+joy.leftX())*power)>1:
        leftPower = 1
    else:
        leftPower = (1+joy.leftX())*power
    
    

    setRightPower(power)
    setLeftPower(power)

    if joy.A():
        if collectOn:
            GPIO.output(collectPin, GPIO.LOW)
            collectOn = False
        else:
            GPIO.output(collectPin, GPIO.HIGH)
            collectOn = True
        
        while joy.A():
            time.sleep(.0001)

    #GPIO.add_event_detect(countPin, GPIO.RISING)

    #if GPIO.event_detected(countPin):
        #ballCount+=1

    print("right: " + fmtFloat(leftPower))


    # Show connection status
    
    #showIf(joy.connected(), "Y", "N")
    # Left analog stick
    #show("  Left X/Y:", fmtFloat(joy.leftX()), "/", fmtFloat(joy.leftY()))
    # Right trigger
    
    #show("  RightTrg:", fmtFloat(joy.rightTrigger()))
    # A/B/X/Y buttons
    #show("  LeftTrg:", fmtFloat(joy.leftTrigger()))
    #show("  Buttons:")
    
      
    
# Close out when done
GPIO.cleanup()
joy.close()
