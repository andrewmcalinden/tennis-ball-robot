# simple operations used by py-code on Rpi
import socket
import pigpio
import sys

#========================
def isRPi(rospy=0):
    hostname=socket.gethostname()
    if not 'rpi' in hostname:
        text="host=%s is not R-Pi, can't access GPIO pins, abort\n"%hostname
        if rospy:
            rospy.logerr(text )
        else:
            print text
      
        exit(3)
        
#========================
def getGPIO(rospy=0):
    piDrv=pigpio.pi()
    if not piDrv.connected:
        text="pigpio initialisation failed, try :\n   ps -ef |grep  pigpiod  \n  sudo pigpiod\n"
        if rospy:
            rospy.logerr(text )
        else:
            print text
        exit(1)

    return piDrv

#========================
def dumpPIGIOver(piDrv):

   print("\nTesting pigpio Python module {}".format(pigpio.VERSION))

   print("Python {}".format(sys.version.replace("\n", " ")))

   print("pigpio version {}.".format(piDrv.get_pigpio_version()))

   print("Hardware revision {}.".format(piDrv.get_hardware_revision()))

