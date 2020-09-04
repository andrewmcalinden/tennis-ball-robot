#!/bin/bash

# Default: Set up GPIO 4 and set to output
pin=${1-4}


echo ${pin} > /sys/class/gpio/export
echo "out" > /sys/class/gpio/gpio${pin}/direction

ls -l /sys/class/gpio/

for (( i=1; i <= 50; i++ ))
do
  echo $1 blink GPIO pin=${pin}  ON 
  echo 1 > /sys/class/gpio/gpio${pin}/value
  sleep 1s
  echo off
  echo 0 > /sys/class/gpio/gpio${pin}/value
  sleep 1s
done

# Clean up
echo ${pin} > /sys/class/gpio/unexport



