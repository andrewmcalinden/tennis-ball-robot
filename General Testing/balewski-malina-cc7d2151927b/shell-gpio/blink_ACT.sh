#!/bin/bash
echo blinks 5x1sec green LED normaly connected to disc I/O
echo none > /sys/class/leds/led0/trigger
for (( i=1; i <= 5; i++ ))
do
  echo 1 > /sys/class/leds/led0/brightness
  sleep 1s
  echo 0 > /sys/class/leds/led0/brightness
  sleep 1s
done
echo mmc0 > /sys/class/leds/led0/trigger

