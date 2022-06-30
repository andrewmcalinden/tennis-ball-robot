import urllib.request
import cv2
import numpy as np 
import os
import shutil

# path = 'https://picsum.photos/200/200'
path = 'https://source.unsplash.com/random/200x200'


def get_number_of_files_in_directory(dir_name):
    path, dirs, files = next(os.walk(dir_name))
    return len(files)


def save_random_grayscale_image(image_path):
    urllib.request.urlretrieve(path, image_path)
    img = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
    cv2.imwrite(image_path, img)

    
def check_if_image_not_exists(image_path):
    image = cv2.imread(image_path)
    listdir_original = os.listdir('neg')
    original = True
    for img_to_compare in listdir_original:
        possible_duplicate = cv2.imread('neg/' + str(img_to_compare))
        if(not (np.bitwise_xor(possible_duplicate, image).any())):
            original = False
            break
    return original


def save_images():
    if(not os.path.exists('tmp')):
        os.makedirs('tmp')
    if(not os.path.exists('neg')):
        os.makedirs('neg')
    id=0
    while(id<3600):
        id = get_number_of_files_in_directory('neg')
        image_path = f"tmp/{str(id + 1)}.jpg"
        save_random_grayscale_image(image_path)

        if(check_if_image_not_exists(image_path)):
            print(f"Picture added to directory, currently {id + 1} negative pictures")
            shutil.copyfile(image_path, f"neg/{str(id + 1)}.jpg")
        else:
            print(f"Picture already in directory, currently {id} negative pictures")


save_images()
