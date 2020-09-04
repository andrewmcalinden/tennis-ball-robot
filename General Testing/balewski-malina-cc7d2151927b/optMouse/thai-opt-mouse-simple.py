#!/usr/bin/env python

"""
The measure moves to the horizontal (X) and vertical (Y) is important for the control and the robot needs to know the position after the movement of equipment such as robotic cars that need within walking distance.

The first byte is the status of the mouse. Each bit has the following meaning:

Bit 0 - The status of the Left (= 1 hit, 0 = release).
Bit 1 - the state of the right button.
Bit 2 - The status of the middle button (if any).
Bit 3 - do not take up as one always.
Bit 4 - motion in the horizontal axis (X) by 1 = move left, move to the right = 0.
Bit 5 - Set direction Cannes (Y) = edged down by 1, 0 = moved up.
Bit 6 - Overflow horizontal axis is one variable when the mouse moves too fast for the full value (the value exceeds +/- 127).
Bit 7 - Overflow vertical axis

BYTE 2: the horizontal axis motion. keep distance since previous reading. The values will ratain 2s complement 9-128,+127)

BYTE 3 : The vertical axis movement.

Taken from :

http://learninginventions.org/%E0%B8%84%E0%B8%A5%E0%B8%B1%E0%B8%87%E0%B8%84%E0%B8%A7%E0%B8%B2%E0%B8%A1%E0%B8%A3%E0%B8%B9%E0%B9%89-raspberry-pi/%E0%B8%81%E0%B8%B2%E0%B8%A3%E0%B9%83%E0%B8%8A%E0%B9%89-optical-mouse-%E0%B9%80%E0%B8%9E%E0%B8%B7%E0%B9%88%E0%B8%AD%E0%B8%A7%E0%B8%B1%E0%B8%94%E0%B8%81%E0%B8%B2%E0%B8%A3%E0%B9%80%E0%B8%84%E0%B8%A5/


"""


import time

f = open('/dev/input/mouse1', 'rb')

xpos = 0
ypos = 0

print "started"
while True:
        # read from the file. ord() converts char to integer
        state = ord(f.read(1))
        dx = ord(f.read(1))
        dy = ord(f.read(1))
 
        #convert bits in 'state' in to an array 'mouse_state'
        mouse_state = [(state & (1 << i)) >> i for i in xrange(8)]
 
        # if mouse moving to the left. dx must be a negative value
        if mouse_state[4] == 1:
                dx = dx - 256    # convert 2's complement negative value
 
        # if mouse moving down
        if mouse_state[5] == 1:
                dy = dy - 256
 
        if (mouse_state[6] == 1) or (mouse_state[7]==1):
                print "Overflow!"
 
        # update the position
        xpos += dx
        ypos += dy
 
        print "DX=%4d  DY=%4d, xpos=%6d  ypos=%6d" % (dx,dy,xpos,ypos)

