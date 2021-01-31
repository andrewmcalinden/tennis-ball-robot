from __future__ import print_function

import xbox

# Format floating point number to string format -x.xxx
def fmtFloat(n):
    return '{:6.3f}'.format(n)

# Print one or more values without a line feed
def show(*args):
    for arg in args:
        print(arg, end="")

# Print true or false value based on a boolean, without linefeed
def showIf(boolean, ifTrue, ifFalse=" "):
    if boolean:
        show(ifTrue)
    else:
        show(ifFalse)

# Instantiate the controller
joy = xbox.Joystick()

# Show various axis and button states until Back button is pressed
print("Xbox controller sample: Press Back button to exit")
while not joy.Back():
    # Show connection status
    show("Connected:")
    showIf(joy.connected(), "Y", "N")
    # Left analog stick
    show("  Left X/Y:", fmtFloat(joy.leftX()), "/", fmtFloat(joy.leftY()))
    # Right trigger
    
    show("  RightTrg:", fmtFloat(joy.rightTrigger()))
    # A/B/X/Y buttons
    show("  LeftTrg:", fmtFloat(joy.leftTrigger()))
    show("  Buttons:")
    showIf(joy.A(), "A")
    show(chr(13))
# Close out when done
joy.close()
