#!/bin/bash
# uses the wiringPi -library
# Default: Set up GPIO 5 and set to output
pin=${1-4}
nLoop=${2-3}
echo It will toggel $nLoop times gpioPin=$pin   

gpio -g mode ${pin} out

for (( i=1; i <= $nLoop; i++ )) ; do
    echo $i blink pin=${pin}  ON 
    gpio -g write ${pin} 1
    sleep 2s
    echo pin-off
    gpio -g write ${pin} 0
    sleep 1s
done

echo NO Clean up

ls -l /sys/class/gpio/



