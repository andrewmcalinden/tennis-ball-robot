#!/usr/bin/env python


import subprocess
task = subprocess.Popen("cat /proc/bus/input/devices", shell=True, stdout=subprocess.PIPE)
data = task.stdout.read()
assert task.wait() == 0
#print('dataByte=',data)
#print('dataStr=',data.decode('utf-8'))
#exit(1)

m=0
for line in data.decode('utf-8').split("\n"):
#    print line
    if "H: Handlers=mouse" in line:
        print line
