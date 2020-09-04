#!/usr/bin/python
#
# Generic example of GUI : main
# Author: Jan Balewski (jan.balewski@gmail.com)
#
import math
from math import pi as PI

from stubGUI import *
from optparse import OptionParser

#===============================
#=======   define   main_run()
#===============================
def main_run():
  
    rootWin = Tkinter.Tk()
    rootWin.title( 'Stub GUI XYZ' )
    rootWin.resizable( 0, 0 )

    # connect particular GUI
    app = ApplicationGUI(rootWin,options.SERVOS)
    print "====M: init completed ========"

    #..... recursive function updating GUI
    def update_gui():
        rootWin.after(10, update_gui)

    #  ... self-loop activated   
    update_gui()
  
    #..... emergency termination of controll app
    rootWin.protocol( 'WM_DELETE_WINDOW', app.actExit)
    try:
        app.actStart()
    except:
        app.actExit()


#===============================
#=======    MAIN Program
#===============================

if __name__ == '__main__':
    
    # -- command line options
    usage = "usage: %prog [options]"
    parser = OptionParser(usage)

    parser.add_option("-s","--servos", 
                      dest="SERVOS", 
                      action="store_true", 
                      help="toggle spill", 
                      default = True)
    
    parser.add_option("-v","--verbose", 
                      dest="VERBOSE", 
                      action = "store_true", 
                      help="print aux info", 
                      default = False)
 
    (options,args) = parser.parse_args()
  

    if options.VERBOSE:
        print ">>> Executing with parameters:"
        print ">>> SERVOS = %s" % options.SERVOS # True = On, False = Off
 

    #################################
    #  RUN  MAIN
    #################################

    main_run()
