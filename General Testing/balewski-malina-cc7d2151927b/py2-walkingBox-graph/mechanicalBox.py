#!/usr/bin/python

# mechnicalBox.py
# ----------
# Licensing Information:  You are free to use or extend these projects for 
# educational purposes provided that (1) you do not distribute or publish 
# solutions, (2) you retain this notice, and (3) you provide clear 
# attribution to UC Berkeley, including a link to 
# http://inst.eecs.berkeley.edu/~cs188/pacman/pacman.html
# 
# exammple of modeling of a rectangle moving in space in the x-direction
# Jan Balewski, PanAlgo LLC, April 2015
#

import math
from math import pi as PI
import time
class CrawlingRobot:

    def getRotationAngle(self):
        """
            get the current angle (rad) by which  the
            robot body is rotated off the ground
        """
        return 0.8
        
    def getRobotPosition(self):
        """
        returns the (x,y) coordinates
        of the lower-left point of the robot
        """
        return self.robotPos

    def moveRobotPosition(self,dx,dy):
        """
        computes new position 
        of the lower-left point of the robot
        """
        (x,y)= self.robotPos
        self.robotPos=(x+dx,y+dy)


    def __getCosAndSin(self, angle):
        return math.cos(angle), math.sin(angle)


    def draw(self, stepCount):
        x1, y1 = self.getRobotPosition()
        x1 = x1 % self.totWidth

        ## Check Lower Still on the ground
        if y1 != self.groundY:
            raise 'Flying Robot!!'

        rotationAngle = self.getRotationAngle()
        cosRot, sinRot = self.__getCosAndSin(rotationAngle)


        x2 = x1 + self.robotWidth * cosRot
        y2 = y1 - self.robotWidth * sinRot

        x3 = x1 - self.robotHeight * sinRot
        y3 = y1 - self.robotHeight * cosRot

        x4 = x3 + cosRot*self.robotWidth
        y4 = y3 - sinRot*self.robotWidth

        self.canvas.coords(self.robotBody,x1,y1,x2,y2,x4,y4,x3,y3)

        # Position and Velocity Sign Post
        steps = (stepCount - self.lastStep)
        if steps==0:return
        pos = self.getRobotPosition()[0]
        positionMsg = 'Position: %2.f' % pos
        stepMsg = 'Step: %d' % stepCount

        if 'step_msg' in dir(self):
            self.canvas.delete(self.pos_msg)
            self.canvas.delete(self.step_msg)

        self.pos_msg = self.canvas.create_text(250,190,text=positionMsg)
        self.step_msg = self.canvas.create_text(50,190,text=stepMsg)
        self.lastStep = stepCount


    def __init__(self, canvas):

        ## Canvas ##
        self.canvas = canvas
        self.lastStep = 0

        ## Draw Ground ##
        self.totWidth = canvas.winfo_reqwidth()
        self.totHeight = canvas.winfo_reqheight()
        self.groundHeight = 40
        self.groundY = self.totHeight - self.groundHeight

        self.ground = canvas.create_rectangle(0,
            self.groundY,self.totWidth,self.totHeight, fill='blue')

        ## Robot Body ##
        self.robotWidth = 80
        self.robotHeight = 40
        self.robotPos = (20, self.groundY)
        self.robotBody = canvas.create_polygon(0,0,0,0,0,0,0,0, fill='green')


if __name__ == '__main__':
    print "jan-main: start mechanical box simulation"
    from graphicsBoxDisplay import *
    run_main()
