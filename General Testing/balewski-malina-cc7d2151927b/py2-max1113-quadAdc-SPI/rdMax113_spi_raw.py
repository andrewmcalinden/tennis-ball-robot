#!/usr/bin/env python
import time

"""
reading MAX1113 directly with read

seams to not being able to distinguish CE0 from CE1

"""

def readAdc(adcChan, spiChan=0):
	if adcChan == 0:
		cmd = chr(int('10001111',2))
	if adcChan  == 1:
		cmd = chr(int('11001111',2))
	if adcChan  == 2:
		cmd = chr(int('10101111',2))
	if adcChan  == 3:
		cmd = chr(int('11101111',2))

 	####note this will actually bring CS high between write and read
	####which may not work for all devices but it works with this device
	#write to ADC to choose channel
	#f = open('/dev/spidev0.0','w')
	spiDev='/dev/spidev0.'+str(spiChan)
	#print 'read adcCh=',adcChan,' spiDevChan=',spiDev
	f = open(spiDev,'w')
	f.write(cmd)
	f.close()
	#read from ADC
	f = open(spiDev,'r')
	data = f.read(2)
	db = bytearray(data)
	#data format 0-0-msb-x-x-x-x-x-x-lsb-0-0-0-0-0-0
	value = (db[0]<<2) | (db[1]>>6)
	return value

spiChan=0
print "read once all 4 channels of MAX113 , spiChan=",spiChan
for ch in range(4):
    print ch , readAdc(ch,spiChan)

adcCh=2
delT=0.001
print "read  only ch=%d in infinite loop"%ch
n=0
while True:
     print n,adcCh , readAdc(adcCh,spiChan)
     n+=1
     time.sleep(delT) # sleep in seconds
