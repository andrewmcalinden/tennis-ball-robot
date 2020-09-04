#!/usr/bin/python
'''
 Read integral of pulses using 2-byte depth counter
 Reading indirectly from CNTR via OTR register 
It should NOT  disrupt  continus counting by CNTR
'''


def readCntr( nw , cmd=0b01100111): 
#   cmd=0b01100111 ; txt="RD:CNTR"; 
   cmdL=[cmd]
   for i in range(nw):
       cmdL+=[(i+1)*10] # dummy vars feed during shiftout

   #print nw," cmdL=",cmdL ," cmd=0b",format( cmd,'08b' )
   resp = spi.xfer2(cmdL) # transfer data 2 ways
   sum=0
   #print "   rd-data:",
   for i in range (nw):
        oneByte=resp[i+1];
        #print "0x%0X=%s  "%(resp[i+1],format( resp[i+1],'08b') ),
        sum=sum+ oneByte<<(nw-1-i)*8
   #print ""
   return sum

def doCmd(txt,cmd,data0=0,data1=0):
    cmdL=[cmd,data0,data1]
    resp = spi.xfer2(cmdL) # transfer one byte
    #print txt," cmd=0x%0x=%s -->  ans=0x%0X=%s"%(cmdL[0],bin(cmdL[0]),resp[1],bin(resp[1]))
   # time.sleep(0.1) # sleep for 0.1 seconds

#------------------
#   MAIN 
#------------------

import spidev
import time
spi = spidev.SpiDev() # create spi object
spi.open(0, 0) # open spi port 0, device (CS0) 

numWord=2
delT=0.1  # seconds


spi.max_speed_hz=10000000
print "using bits_per_word=",spi.bits_per_word
print "using max_speed_hz=", spi.max_speed_hz

# setting registers to
print "reading numWord=",numWord," and 2*400 counts per 360 deg"
''' MDR0 register
  b01: 1 counts per qudrature cycle
  b10: 2 counts per qudrature cycle
  b11: 4 counts per qudrature cycle
'''
cmd=0b10001000 ; txt="WR:MDR0" ;doCmd(txt,cmd,0x3)  

'''  MDR1 register
   b00 : 4 byte depth counter
   b10 : 2 byte depth counter
'''
cmd=0b10010000 ; txt="WR:MDR1" ;doCmd(txt,cmd,0x2) 

# read register values back
cmd=0b01001000 ; txt="RD:MDR0"; doCmd(txt,cmd)
cmd=0b01010000 ; txt="RD:MDR1"; doCmd(txt,cmd)

# reading current counter and set is as zero:
nPulses0= readCntr(numWord, 0b01100000) 
print "starting counter value=",nPulses0

mxUint16=65535
minCnt=0; maxCnt=0;
n=0
try:
 while True:     
     cmd=0b11101000 ; txt="LT:OTR"; doCmd(txt,cmd)
     nPulses= readCntr(numWord,  0b01101000) # read OTR instead of CNTR 
     relPulses=  nPulses-nPulses0
     if relPulses < -mxUint16/2 :
         relPulses+=mxUint16
     if relPulses > mxUint16/2 :
         relPulses-=mxUint16
     if minCnt>relPulses:
         minCnt=relPulses
     if maxCnt<relPulses:
         maxCnt=relPulses
     #print "n=",n,' nPules=',nPulses,  ' change=',relPulses
     print "n=",n,' relPulses=',relPulses, ' Min/Max=',minCnt,maxCnt, " avrAmpl=", (-minCnt+maxCnt)/2," delAmpl=",minCnt+maxCnt
     n+=1
     time.sleep(delT) # sleep in seconds

except KeyboardInterrupt: # Ctrl+C pressed,
    spi.close() # close the port before exit


spi.close(); exit(1) # close the port before exit
