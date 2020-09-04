#!/usr/bin/env python

#========================
#========================
#========================
class I2c_for_Adafruit:
    """ translates pigpio to adafruit"""

    def __init__(self,drv):
        self.rpiDrv=drv
        print "i2c_for_adafruit init "
        
    def close(self):
        self.rpiDrv.i2c_close(self.i2c_hn) 
        """ call it at the end to avoid running out of handels"""

    def get_i2c_handle(self): 
        return self.i2c_hn

    def get_i2c_device(self, address):        
        hn = self.rpiDrv.i2c_open(1, address)
        self.i2c_hn=hn
        print "i2c_ala open add(0x)=%0x"%address," hn=",hn
        return self

    def write8(self, MODE2, OUTDRV):
        #print "i2c_ala  wr8 mode=%d val/0x=%0d"%( MODE2, OUTDRV)
        self.rpiDrv.i2c_write_byte_data(self.i2c_hn, MODE2, OUTDRV)

    def readU8(self, MODE1):
        #print "i2c_ala  rd8 mode=%d "%( MODE1)
        val=self.rpiDrv.i2c_read_byte_data(self.i2c_hn, MODE1)
        return val

        
    def softwareReset(self):
        hn2=self.rpiDrv.i2c_open(1,0x00)
        self.rpiDrv.i2c_write_device(hn2,b'\x06')  # SWRST
        self.rpiDrv.i2c_close(hn2)
        """Sends a software reset (SWRST) command to 
        all servo drivers on the bus."""

################################
#     MAIN
################################
if __name__ == '__main__':
    i2cDrv=I2c_for_Adafruit('abc')
    print 'salute=I2c'    
    exit()

