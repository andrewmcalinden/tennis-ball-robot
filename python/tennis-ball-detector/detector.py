import cv2
import sys
import os

directory = sys.argv[1]
classifier = sys.argv[2]

classifier = cv2.CascadeClassifier(classifier)
images_to_check = os.listdir(directory)

if(not os.path.exists('results')):
    os.makedirs('results')

for image in images_to_check:
    img = cv2.imread(f"{directory}/{image}")
    img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    found = classifier.detectMultiScale(img_gray, minSize =(40, 40))
    if(len(found)!=0):
        with open(f"results/{image[:-4]}_balls.txt", 'w') as f:
            for i, (x, y, width, height) in enumerate(found):
                cv2.rectangle(img, (x, y), (x + height, y + width), (0, 255, 0), 5)
                f.write(f"ball_no_{i}: coords ({x}, {y}), size {height}x{width}\n")
    cv2.imwrite(f"results/{image}", img)
    
