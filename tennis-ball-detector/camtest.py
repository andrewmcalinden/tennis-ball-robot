import cv2
import sys
import os
import time

# Run Command:
#python3 camtest.py




fpsLimit = 2 # throttle limit
startTime = time.time()
cap = cv2.VideoCapture(0)



while True:
    img = cap.read
    nowTime = time.time()
    if (int(nowTime - startTime)) > fpsLimit:
        
        #img_gray = cv2.cvtColor(cv2.UMat(img), cv2.COLOR_BGR2GRAY)
        
        cv2.imshow(img)
        startTime = time.time() # reset time
