import math
from math import atan2, sin, cos, radians
import time

class Controller():
    def __init__(self, start_, goal_, R_ = 0.0325, L_ = 0.1, kP = 0.1, kI = 0.01, kD = 0.1, dT = 0.1, v=1.0):
        self.current = start_
        self.goal = goal_
        self.R = R_ #in meter
        self.L = L_ #in meter

        self.E = 0  #Cummulative error
        self.old_e = 0 # Previous error

        self.Kp = kP
        self.Ki = kI
        self.Kd = kD

        self.desiredV = v
        self.dt = dT #in second
        return

    
    def uniToDiff(self, v, w):
        vR = (2*v + w*self.L)/(2*self.R)
        vL = (2*v - w*self.L)/(2*self.R)
        return vR, vL

    
    def diffToUni(self, vR, vL):
        v = self.R/2*(vR+vL)
        w = self.R/self.L*(vR-vL)
        return v, w
    

    def iteratePID(self):
        #Difference in x and y
        d_x = self.goal.x - self.current.x
        d_y = self.goal.y - self.current.y

        #Angle from robot to goal
        g_theta = atan2(d_y, d_x)

        #Error between the goal angle and robot angle
        alpha = g_theta - self.current.theta
        #alpha = g_theta - math.radians(90)
        e = atan2(sin(alpha), cos(alpha))
        

        e_P = e
        e_I = self.E + e
        e_D = e - self.old_e

        # This PID controller only calculates the angular velocity with constant speed of v
        # The value of v can be specified by giving in parameter or using the pre-defined value defined above.
        w = self.Kp*e_P + self.Ki*e_I + self.Kd*e_D

        w = atan2(sin(w), cos(w))

        self.E = self.E + e
        self.old_e = e
        v = self.desiredV

        return v, w
