#!/usr/bin/env python

import matplotlib.pyplot as plt
import time
import random
import math

import scipy
from scipy import *

#j import emant

from scipy import fft, ifft
print 'J:start0'
MAINS_FREQ = 60
NOTCH_LENGTH_AVERAGE = 4
ScanRate = MAINS_FREQ * NOTCH_LENGTH_AVERAGE
NumSamples = ScanRate * 2 + NOTCH_LENGTH_AVERAGE 

print 'J:start1'
def HighPass(ECGdata):
    fftECG = fft(ECGdata)
    for i in range(len(fftECG)):
        if i<8 or i>(NumSamples-NOTCH_LENGTH_AVERAGE-8): fftECG[i]=0    
    return ifft(fftECG)

def NotchMains(ECGdata):
    filteredECG=[]
    for i in range(len(ECGdata)-NOTCH_LENGTH_AVERAGE):
        filteredECG.append((sum(ECGdata[i:(i+NOTCH_LENGTH_AVERAGE)])/NOTCH_LENGTH_AVERAGE))
    return filteredECG

print 'J:start2'
#j m = emant.Emant300()

#change this mac address to your EMANT380 Bluetooth DAQ module
#j m.Open("00:06:66:00:A1:D8",True)
#j print "Hardware Id: " + m.HwId()

#j r,actScanRate = m.ConfigAnalog(1, emant.Emant300.Bipolar, ScanRate)
#j print "Actual Scan Rate: " + str(actScanRate)

fig = plt.figure()
ax = fig.add_subplot(3, 1, 1)
bx = fig.add_subplot(3, 1, 2)
cx = fig.add_subplot(3, 1, 3)

# Create a new timer object. Interval set to 2.5 secs 
timer = fig.canvas.new_timer(interval=500)

loop = True
nl=0

def update_graph(axesa,axesb,axesc):
    global timer, loop,nl
    if loop:
        nl+=1
	print 'J:start4, nl=',nl
        #ECGdata = m.ReadAnalogWaveform(emant.Emant300.AIN2,emant.Emant300.AIN3,NumSamples)
        ECGdata=randn(200)
        #print ECGdata
        Notchfiltered = NotchMains(ECGdata)
        HighPassed = HighPass(Notchfiltered)
        
        axesa.cla()
        axesa.plot(ECGdata[10:NumSamples-10])  # update the data
        axesb.cla()
        axesb.plot(Notchfiltered[10:NumSamples-10])
        axesc.cla()
        axesc.plot(HighPassed[10:NumSamples-10])
        axesa.figure.canvas.draw()

    else:
        plt.close()

def onclick(event):
    global loop
    loop = not(event.button==3)

# right mouse click on graph to end program
cid = fig.canvas.mpl_connect('button_press_event', onclick)


# tell the timer what function should be called
timer.add_callback(update_graph, ax, bx, cx)

update_graph(ax,bx,cx)
timer.start()

plt.show()
timer.stop()
m.Close()
