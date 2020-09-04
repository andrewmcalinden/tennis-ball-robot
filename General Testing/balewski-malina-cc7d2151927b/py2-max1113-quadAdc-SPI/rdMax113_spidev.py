#!/usr/bin/env python
import time
import spidev

"""
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
print "read once all 4?? channels of MAX113 , spiChan=",spiChan

spi = spidev.SpiDev() # create spi object
spi.open(0, spiChan) # open spi port, device (CS0)
spi.max_speed_hz=500000
print "using bits_per_word=",spi.bits_per_word
print "using max_speed_hz=", spi.max_speed_hz

for ch in range(4):
    print 'ch=',ch , readAdc(ch,spiChan)


delT=0.1
adcCh=1
print "read  only ch=%d in infinite loop"%ch
n=0
while True:
     print n,adcCh , readAdc(adcCh,spiChan)
     n+=1
     time.sleep(delT) # sleep in seconds
