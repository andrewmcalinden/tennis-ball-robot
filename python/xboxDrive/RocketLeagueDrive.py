from __future__ import print_function
import RPi.GPIO as GPIO
import xbox

GPIO.setmode(GPIO.BCM)


p = GPIO.PWM(17, 3000)
p.start(0)



# Format floating point number to string format -x.xxx
def fmtFloat(n):
    return '{:6.3f}'.format(n)


# Instantiate the controller
joy = xbox.Joystick()

# Show various axis and button states until Back button is pressed
print("Xbox controller sample: Press Back button to exit")
while not joy.Back():
    # Show connection status
    
    #showIf(joy.connected(), "Y", "N")
    # Left analog stick
    #show("  Left X/Y:", fmtFloat(joy.leftX()), "/", fmtFloat(joy.leftY()))
    # Right trigger
    
    #show("  RightTrg:", fmtFloat(joy.rightTrigger()))
    # A/B/X/Y buttons
    #show("  LeftTrg:", fmtFloat(joy.leftTrigger()))
    #show("  Buttons:")
    
        p.ChangeDutyCycle(100*joy.leftY())
    
# Close out when done
joy.close()
