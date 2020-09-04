#!/usr/bin/python
'''
 Read integral of pulses using 4-byte depth counter

'''


def BytesToHex(Bytes):
 return ''.join(["0x%02X " % x for x in Bytes]).strip()

def doCmd(txt,cmd,data0=0,data1=0):
    cmdL=[cmd,data0,data1,0xc1,0xc2,0xc3]
    resp = spi.xfer2(cmdL) # transfer one byte
    #print txt," cmd=0x%0x=%s --> "%(cmdL[0],bin(cmdL[0]))
    sum=0
    #print "   rd-data:",
    for i in range (4):
        oneByte=resp[i+1];
        #print "0x%0X=%s  "%(resp[i+1],bin(resp[i+1])),
        sum=sum+ oneByte<<(3-i)*8
    #print ""
    return sum

import spidev
import time
spi = spidev.SpiDev() # create spi object
spi.open(0, 0) # open spi port 0, device (CS0) 

print "using bits_per_word=",spi.bits_per_word
print "using max_speed_hz=", spi.max_speed_hz


n=0
try:
 while True:
     cmd=0b01100111 ; txt="RD:CNTR"; 
     nPulses=doCmd(txt,cmd)
     print "n=",n,' nPules=',nPulses
     n+=1
     time.sleep(0.5) # sleep for 0.1 seconds
 #end while
except KeyboardInterrupt: # Ctrl+C pressed,
    spi.close() # close the port before exit
#end try




spi.close(); exit(1) # close the port before exit
