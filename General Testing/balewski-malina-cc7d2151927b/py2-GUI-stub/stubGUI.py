#
# Generic example of GUI : app
# Author: Jan Balewski (jan.balewski@gmail.com)
#
import time
import threading
import sys
import math
import Tkinter
from math import pi as PI

servoType = 'standardServo'

#--------------------------------------------
#------ define class GUIApplication:
#--------------------------------------------

class ApplicationGUI:

    def sigmoid(self, x):
        return 1.0 / (1.0 + 2.0 ** (-x))

    def incrementAlpha(self, inc):
        self.alphaPower += inc
        self.alpha = self.sigmoid(self.alphaPower)
        self.alpha_label['text'] = 'alpha: %.2g' % (self.alpha)

    def updateA(self):
        self.arm_angle['text'] = 'ang/deg=%.0f' % (self.armAngle/PI*180)        

    def setupA(self):
        rowC=0; colC=0
        label1 = Tkinter.Label(self.win, text='ABC')
        label1.grid(row=rowC, column=colC)
        self.armAngle = 1. #rad

        #--- arm angle
        mid = Tkinter.Button(self.win,text="reset",command=(lambda: self.actMove('reset')))
        mid.grid(row=rowC, column=colC+1, padx=10) 
        bot = Tkinter.Button(self.win,text="set",command=(lambda: self.actMove('set')))
        bot.grid(row=rowC+1, column=colC+1, padx=10) 

        self.arm_angle = Tkinter.Label(self.win, text='ang/deg=:X ')
        self.arm_angle.grid(row=rowC+4, column=colC) 

        
    def __initGUI(self, win):
        ## Window ##
        self.win = win

        ## Initialize Frame ##
        win.grid()
  
        ## Alpha Button + Label ##
        self.setupAlphaButtonAndLabel(win)

        ## Exit Button ##
        self.exit_button = Tkinter.Button(win,text='Quit', command=self.actExit)
        self.exit_button.grid(row=0, column=9)

        self.setupA()
  

    def setupAlphaButtonAndLabel(self, win):
        col=8; row=3
        self.alpha_minus = Tkinter.Button(win,
                text="-",command=(lambda: self.incrementAlpha(self.sigDec)))
        self.alpha_minus.grid(row=row, column=col, padx=10) ; row+=1

        self.alpha = self.sigmoid(self.alphaPower)        
        self.alpha_label = Tkinter.Label(win, text='alpha: %.2g' % (self.alpha))
        self.alpha_label.grid(row=row, column=col) ; row+=1

        self.alpha_plus = Tkinter.Button(win,
                text="+",command=(lambda: self.incrementAlpha(self.sigInc)))
        self.alpha_plus.grid(row=row, column=col, padx=10)


    # --------------------------       
    def __init__(self, win, servosOn):

        # those are increments for respective values if +/-button is pressed
        self.alphaPower = 2
        self.sigDec = -.5
        self.sigInc = .5
  
        self.__initGUI(win) ## Init Gui

        # Init environment
        if servoType ==  'standardServo':
            # self.servoDriver = CrawlingRobotBody(self.canvas2D,servosOn)
            x=1
        else:
            raise "Unknown RobotType"

        self.useServos=servosOn
        self.updateA()    

    def actMove(self,action):
        print 'actMove action=',action
  
        if action=='reset':
            print 'reset angle it is'
            self.armAngle=0
            
        if action=='set':
            self.armAngle=self.alpha
        self.updateA()    

    def actExit(self):
        try:
            self.win.destroy()
        except:
            pass
    
        if  self.useServos:
            #1 self.servos.fullStop()
            self.useServos=False # to prevent multiple stops
            
        sys.exit(0)

 
    def actStart(self):
        self.win.mainloop()



 
