from __future__ import print_function
import RPi.GPIO as GPIO
import xbox

GPIO.setmode(GPIO.BCM)

GPIO.setup(17, GPIO.OUT)




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
    if joy.A():
        GPIO.output(17, 1)
    else:
        GPIO.output(17, 0)
    
# Close out when done
joy.close()
