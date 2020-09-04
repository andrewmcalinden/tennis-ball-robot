#!/usr/bin/env python
import time
import spidev

"""
Reading 3 pots + 2 switches for pendulum controll
reading MAX1113  w/ spidev object

"""

def readAdc(adcChan, spiChan=0):
    sel2=adcChan%2
    sel1=adcChan/2
    cmd= ((2*sel2+sel1) <<5) +0b10001111 
    #print 'adcChan=%d cmd=0x%02x'%(adcChan,cmd)
    data0=0; data1=0
    cmdL=[cmd,data0,data1]
    resp = spi.xfer2(cmdL) # transfer one byte    
    #  data format 0-0-msb-x-x-x-x-x-x-lsb-0-0-0-0-0-0
    value = (resp[1]<<2) | (resp[2]>>6)
    #print "resp1,1, 0x%02x 0x%02x"%(resp[1],resp[2])
    #print 'adc val=',value
    return value


spiChan=1
delTsec=0.5
print "read start , spiChan=",spiChan," period/sec=",delTsec

spi = spidev.SpiDev() # create spi object
spi.open(0, spiChan) # open spi port, device (CS0)
spi.max_speed_hz=500000
print "using bits_per_word=",spi.bits_per_word
print "using max_speed_hz=", spi.max_speed_hz
n=0
while True:
    togA=1
    togB=1
    pot={}
    for ch in range(4):
        val= readAdc(ch,spiChan)
        #print 'ch=',ch ,val
        if ch==0:
            if val >200:
                togA=togB=0
            elif val>100:
                togA=0
            elif val>48:
                togB=0
        else :
            pot[ch]=val
    print n,"togA=%d togB=%d"%(togA,togB),pot
    n+=1
    time.sleep(delTsec) # sleep in seconds
