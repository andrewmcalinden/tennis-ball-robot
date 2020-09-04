# graphicsCrawlerDisplay.py
# -------------------------
# Licensing Information:  You are free to use or extend these projects for 
# educational purposes provided that (1) you do not distribute or publish 
# solutions, (2) you retain this notice, and (3) you provide clear 
# attribution to UC Berkeley, including a link to 
# http://inst.eecs.berkeley.edu/~cs188/pacman/pacman.html
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero 
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and 
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


import Tkinter
import time
import threading
import sys
import mechanicalBox
import math
from math import pi as PI

robotType = 'mechanicalBox'

class Application:

    def sigmoid(self, x):
        return 1.0 / (1.0 + 2.0 ** (-x))

    def incrementSpeed(self, inc):
        self.tickTime *= inc
        self.speed_label['text'] = 'Step Delay: %.5f' % (self.tickTime)


    def __initGUI(self, win):
        ## Window ##
        self.win = win

        ## Initialize Frame ##
        win.grid()
        self.dec = -.5
        self.inc = .5
        self.tickTime = 0.05

        ## Epsilon Button + Label ##
        self.setupSpeedButtonAndLabel(win)
 
        ## Exit Button ##
        self.exit_button = Tkinter.Button(win,text='Quit', command=self.exit)
        self.exit_button.grid(row=0, column=9)

         ## Canvas ##
        self.canvas = Tkinter.Canvas(root, height=200, width=600)
        self.canvas.grid(row=2,columnspan=10)


    def setupSpeedButtonAndLabel(self, win):
        self.speed_minus = Tkinter.Button(win,
        text="-",command=(lambda: self.incrementSpeed(.5)))
        self.speed_minus.grid(row=0, column=0)

        self.speed_label = Tkinter.Label(win, text='Step Delay: %.5f' % (self.tickTime))
        self.speed_label.grid(row=0, column=1)

        self.speed_plus = Tkinter.Button(win,
        text="+",command=(lambda: self.incrementSpeed(2)))
        self.speed_plus.grid(row=0, column=2)


    def __init__(self, win):
        self.stepCount = 0
        
        ## Init Gui
        self.__initGUI(win)

        # Init environment
        if robotType == 'mechanicalBox':
            self.robot = mechanicalBox.CrawlingRobot(self.canvas)
        else:
            raise "Unknown RobotType"

        # Start GUI
        self.running = True
        self.stopped = False
        self.stepsToSkip = 0
        self.thread = threading.Thread(target=self.run)
        self.thread.start()


    def exit(self):
        self.running = False
        for i in range(5):
            if not self.stopped:
                time.sleep(0.1)
        try:
            self.win.destroy()
        except:
            pass
        sys.exit(0)

    def step(self):
        self.stepCount += 1
        # very simple action: move robot by 1 to the right
        self.robot.moveRobotPosition(1,0) 

    def run(self):
        self.stepCount = 0
        while True:
            minSleep = .01
            tm = max(minSleep, self.tickTime)
            time.sleep(tm)
            self.stepsToSkip = int(tm / self.tickTime) - 1

            if not self.running:
                self.stopped = True
                return
            for i in range(self.stepsToSkip):
                self.step()
            self.stepsToSkip = 0
            self.step()
#          self.robot.draw()
        self.learner.stopEpisode()

    def start(self):
        self.win.mainloop()



def run_main():
    global root
    root = Tkinter.Tk()
    root.title( 'Jan mechanicalBox GUI' )
    root.resizable( 0, 0 )

    app = Application(root)

    def update_gui():
        app.robot.draw(app.stepCount)
        root.after(10, update_gui)
    update_gui()

    root.protocol( 'WM_DELETE_WINDOW', app.exit)
    try:
        app.start()
    except:
        app.exit()
