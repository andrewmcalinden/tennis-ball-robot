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
    cmdL=[cmd,data0,data1,0xc1,0xc2,0xc3]
    resp = spi.xfer2(cmdL) # transfer one byte
    print txt," cmd=0x%0x=%s --> "%(cmdL[0],bin(cmdL[0]))
    print "   wr-data:",
    for i in range (4):
        print "0x%0X=%s  "%(cmdL[i+1],bin(cmdL[i+1])),
    print ""

    print "   rd-data:",
    for i in range (4):
        print "0x%0X=%s  "%(resp[i+1],bin(resp[i+1])),
    print ""
    time.sleep(0.1) # sleep for 0.1 seconds

import spidev
import time
spi = spidev.SpiDev() # create spi object
spi.open(0, 0) # open spi port 0, device (CS0) 

print "using bits_per_word=",spi.bits_per_word
print "using max_speed_hz=", spi.max_speed_hz



cmd=0b01100111 ; txt="RD:CNTR"; doCmd(txt,cmd)

cmd=0b10011000 ; txt="WR:DTR"; doCmd(txt,cmd,0xca,0xcb)

cmd=0b11100111 ; txt="DTR2CNTR"; doCmd(txt,cmd,0xca,0xcb)

cmd=0b01100111 ; txt="RD:CNTR"; doCmd(txt,cmd)

cmd=0b00100111 ; txt="CLEAR:CNTR"; doCmd(txt,cmd)

cmd=0b01100111 ; txt="RD:CNTR"; doCmd(txt,cmd)


spi.close(); exit(1) # close the port before exit
