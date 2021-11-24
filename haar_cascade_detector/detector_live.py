import cv2
import sys
import os
import time
import math

# Run Command:
#python3 DetectorRealTime.py data/cascade.xml

classifier = sys.argv[1]

classifier = cv2.CascadeClassifier(classifier)


fpsLimit = 1 # throttle limit
startTime = time.time()
cap = cv2.VideoCapture(0)
cap.set(4, 720)
cap.set(3, 1280)


while True:
    ret_val, img = cap.read()

    #nowTime = time.time()
    #frameRate = 30
    #frameRate = 1/(nowTime - startTime)
    #print("FPS:",frameRate, end="\r")
    img_gray = cv2.cvtColor(cv2.UMat(img), cv2.COLOR_BGR2GRAY)
    found = classifier.detectMultiScale(img_gray, minSize =(10, 10))
    if(len(found)!=0):
        
            for i, (x, y, width, height) in enumerate(found):
                cv2.rectangle(img, (x, y), (x + height, y + width), (0, 255, 0), 5)
                #inches = round(((133.5879*math.e)**(-0.0129*height)), 1)
                print((2.65*1350)/height,"Inches",end="\n")
    cv2.imshow("output", img)
    if cv2.waitKey(1) == 27: 
        break  # esc to quit
    #startTime = time.time() # reset time
cv2.destroyAllWindows()
