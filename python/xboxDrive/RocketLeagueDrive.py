from __future__ import print_function
import RPi.GPIO as GPIO
import xbox
import time
import cv2

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

video = cv2.VideoCapture(0)
   
# We need to check if camera
# is opened previously or not
if (video.isOpened() == False): 
    print("Error reading video file")
  
# We need to set resolutions.
# so, convert them from float to integer.
frame_width = int(video.get(3))
frame_height = int(video.get(4))
   
size = (frame_width, frame_height)
   
# Below VideoWriter object will create
# a frame of above defined The output 
# is stored in 'filename.avi' file.
result = cv2.VideoWriter('filename.avi', 
                         cv2.VideoWriter_fourcc(*'MJPG'),
                         10, size)


# Show various axis and button states until Back button is pressed
print("Xbox Drive: Press Back button to exit")
while not joy.Back():
    
    ret, frame = video.read()
  
    if ret == True: 
  
        # Write the frame into the
        # file 'filename.avi'
        result.write(frame)
    
    power = joy.rightTrigger()-joy.leftTrigger()
    #if (joy.leftX()>0 and joy.leftX()<.75):
        
    rightPower = (1-joy.leftX())*power
    if rightPower>1:
        rightPower = 1
    elif rightPower<-1:
        rightPower = -1
    
    leftPower = (1+joy.leftX())*power
    if leftPower>1:
        leftPower = 1
    elif leftPower<-1:
        leftPower = -1
    
    

    setRightPower(rightPower)
    setLeftPower(leftPower)

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

    #print("right: " + fmtFloat(rightPower))
    #print("left: " + fmtFloat(leftPower))


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

video.release()
result.release()

