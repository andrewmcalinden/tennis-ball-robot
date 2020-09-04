#!/bin/bash
# Runs inifinite loop, recoring it is alive every 60 seconds and beeping 
# Note, uses the wiringPi -library
buzzPin=${1-25}
logFile=heart.log

echo It will buzz  gpioPin=$buzzPin   

gpio -g mode ${buzzPin} out

function buzz {
    delT=$1
    gpio -g write ${buzzPin} 1
    sleep $delT
    #echo pin-off
    gpio -g write ${buzzPin} 0
}


#===============  MAIN =====
echo test buzzer
buzz 1
nPulse=0
echo started measuring at `date` > $logFile
while [ 1 ] ; do

    buzz 0.1
    line="$nPulse minutes alive at `date`"    
    echo  $line>>$logFile 
    echo $line
    nPulse=$[ $nPulse +1 ]
    sleep 60
done

echo NO Clean up

ls -l /sys/class/gpio/



