#!/usr/bin/python
'''
Tries various method

'''

def ReverseBits(byte):
# This script will reverse the bit ordering in one byte (if you are not able to change LSB / MSB 
 byte = ((byte & 0xF0) >> 4) | ((byte & 0x0F) << 4)
 byte = ((byte & 0xCC) >> 2) | ((byte & 0x33) << 2)
 byte = ((byte & 0xAA) >> 1) | ((byte & 0x55) << 1)
 return byte

def BytesToHex(Bytes):
 return ''.join(["0x%02X " % x for x in Bytes]).strip()

def doCmd(txt,cmd,data0=0,data1=0):
    cmdL=[cmd,data0,data1]
    resp = spi.xfer2(cmdL) # transfer one byte
    print txt," cmd=0x%0x=%s -->  ans=0x%0X=%s"%(cmdL[0],bin(cmdL[0]),resp[1],bin(resp[1]))
    time.sleep(0.1) # sleep for 0.1 seconds

import spidev
import time
spi = spidev.SpiDev() # create spi object
spi.open(0, 0) # open spi port 0, device (CS0) 

print "using bits_per_word=",spi.bits_per_word
print "using max_speed_hz=", spi.max_speed_hz


cmd=0b01110000 ; txt="RD:STR"
doCmd(txt,cmd)

cmd=0b10110000 ; txt="WR:STR"
doCmd(txt,cmd,0x00)

cmd=0b01110000 ; txt="RD:STR"
doCmd(txt,cmd)

spi.close(); exit(1) # close the port before exit
