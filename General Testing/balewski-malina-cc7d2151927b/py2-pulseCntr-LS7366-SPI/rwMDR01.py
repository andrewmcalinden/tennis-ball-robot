#!/usr/bin/python
'''
Reads, writes, reads again the MDR0, MDR1 8-bit records to set up pulse-counter to be 2x8 bit long , and to count 4 counts per quadrature cycle
- 

'''

def BytesToHex(Bytes):
 return ''.join(["0x%02X " % x for x in Bytes]).strip()

#----------------
def doCmd(txt,cmd,data0=0,data1=0):
    cmdL=[cmd,data0,data1]
    resp = spi.xfer2(cmdL) # transfer one byte
    print txt," cmd=0x%0x=%s -->  ans=0x%0X=%s"%(cmdL[0],bin(cmdL[0]),resp[1],bin(resp[1]))
    time.sleep(0.1) # sleep for 0.1 seconds

#------------------
#   MAIN 
#------------------
import spidev
import time
spiChan=0
spi = spidev.SpiDev() # create spi object
spi.open(0, spiChan) # open spi port 0, device (CS0) 

print "using bits_per_word=",spi.bits_per_word
print "using max_speed_hz=", spi.max_speed_hz

print 'dump last content of MDR0 , MDR1'
cmd=0b01001000 ; txt="RD:MDR0" ;doCmd(txt,cmd)
cmd=0b01010000 ; txt="RD:MDR1" ;doCmd(txt,cmd)

print 'write new values to MDR0 , MDR1'
# b01: x1 count per qudrature cycle
# b10: x4 counts per qudrature cycle
cmd=0b10001000 ; txt="WR:MDR0" ;doCmd(txt,cmd,0b10)

# b10 : 2 bytes depth counter 
# b11 : 4 bytes depth counter 
cmd=0b10010000 ; txt="WR:MDR1" ;doCmd(txt,cmd,0b11) 

print 'new content of MDR0 , MDR1'
cmd=0b01001000 ; txt="RD:MDR0"; doCmd(txt,cmd)
cmd=0b01010000 ; txt="RD:MDR1"; doCmd(txt,cmd)


spi.close(); exit(1) # close the port before exit
