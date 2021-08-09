import cv2
import sys
import os
import time

# Run Command:
#python3 DetectorRealTime.py data/cascade.xml

classifier = sys.argv[1]

classifier = cv2.CascadeClassifier(classifier)


fpsLimit = 1 # throttle limit
startTime = time.time()
cap = cv2.VideoCapture(0)



while True:
    img = cap.read
    
    img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    found = classifier.detectMultiScale(img_gray, minSize =(10, 10))
    if(len(found)!=0):
        #with open(f"results/{image[:-4]}_balls.txt", 'w') as f:
            for i, (x, y, width, height) in enumerate(found):
                cv2.rectangle(img, (x, y), (x + height, y + width), (0, 255, 0), 5)
                #f.write(f"ball_no_{i}: coords ({x}, {y}), size {height}x{width}\n")
    cv2.imshow(img)
    
