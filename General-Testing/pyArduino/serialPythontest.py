import serial

ser = serial.Serial('/dev/ttyACM0', baudrate = 9600, timeout=1)

def getValues():
    ser.write(b'g')
    incomingData = str(ser.readline())
    incomingData = ''.join(i for i in incomingData if i.isdigit())
    return incomingData

while 1:
    userInput = input('Get data point?')
    
    if userInput == 'y':
        print(getValues())
        
    