# General info
Project for detecting tennis ball using OpenCV library and Python.

# Prerequisites
- `Linux` environment,
- installed `OpenCV` tools [[2]](#2).
- configured `Python` >= 3.6.

# Preconfiguration

```
$ git clone https://github.com/radosz99/tennis-ball-detector.git
$ pip3 install -r requirements.txt
```

# Detail info
To detect item was chosen Haar feature-based cascade classifier proposed by Paul Viola and Michael Jones, which is implemented in OpenCV library.  

Procedure of generating classifier consists of two main steps:
1. Generating `.vec` file based on special prepared file with references to images, coordinates and size of tennis balls (`positives`),
2. Training classifier based on `.vec` file and special prepared file with references to images that does not contain tennis balls (`negatives`).

## Vector file composed of positives
Using Google were collected 25 images that contains tennis balls. Then tennis balls has been cut, cropped to 114x114 pixels and saved to `pos_sample/` directory. Unfortunately, this is not enough to get classifier of great quality, cause there is a need to have at least few hundred of `positives`. Then Ubuntu library `libopencv-dev` comes with help by offering `opencv_createsamples` method that allows to create as many `positives` as we want. Refering to documentation:  

*"...The scheme of test samples creation is similar to training  samples  creation  since  each  test  sample  is  a  background  image into which a randomly distorted and randomly scaled  instance of the object picture is pasted at a random position..."* [[1]](#1).

Using `picture_generatory.py` script 1800 grayscale `negatives` in 200x200 pixels size were collected to `neg/` directory.

To automatize process of generating `positives` bash script was written (`generate_vector.sh`). First of all few variables were defined:
```bash
DIM=$1  # command line argument, to square with the edge with $DIM length wil be cropped image

POS=25  # amount of positive samples
NEG=1800  # amount of negatives
NEG_PER_POS=72  # basically NEG/POS
NEG_PER_POS_2_3=48  # 2/3 * NEG_PER_POS
SAMPLES=1200  # amount of generated positives, NEG_PER_POS_2_3*POS
```
Then in loop to every positive sample have been assigned 72 (`NEG_PER_POS`) negative photos and using `opencv_createsamples` command were created 48 (`NEG_PER_POS_2_3`) positive images for every positive sample. So after this procedure there should be 1200 (`SAMPLES`) positives - 48 per single positive sample with unique negative image as a background:
```bash
for (( i=1; i<=$POS; i++)) do
	START=(i-1)*$NEG_PER_POS
	mkdir net$i
	for (( j=$START + 1; j<=$START+$NEG_PER_POS; j++)) do
		cp neg/$j.jpg net$i
	done
	find net$i -iname "*.jpg" > net$i.txt
	opencv_createsamples -img pos_sample/$i.png -bg net$i.txt -info info$i/info.lst -pngoutput info$i -maxxangle 0.5 -maxyangle 0.5 -maxzangle 0.5 -num $NEG_PER_POS_2_3
	sed "s/^/$i|/" info$i/info.lst >> all/info.lst
	cd info$i
	for file in *.jpg; do
		mv "$file" "../all/$i|$file"
	done
	cd ..
done
```
After executing script above it will be visible directory `all/` with 1200 positive images and file `info.lst` which contains information about all images. In first column there is filename, number before `|` means from which positive sample, image is created. In second amount of tennis balls in this photo, in third and fourth x and y coordinates appropriately and in fifth and sixth height and width in pixels:
```
1|0001_0056_0026_0080_0080.jpg 1 56 26 80 80
...
25|0042_0066_0024_0080_0080.jpg 1 66 24 80 80
25|0043_0065_0040_0056_0056.jpg 1 65 40 56 56
25|0044_0092_0047_0035_0035.jpg 1 92 47 35 35
25|0045_0017_0132_0037_0037.jpg 1 17 132 37 37
```
That `info.lst` file is consumed by command below and vector file `positives.vec` will be created:
```
opencv_createsamples -info all/info.lst -num $SAMPLES -w $DIM -h $DIM -vec positives.vec 
```
In terminal will be visible following output:
```
$...
$ Create training samples from images collection...
$ Done. Created 1200 samples
$ root@vm1:~/home/github/tennis-ball-detector#
```
## Training classifier
For training classifier also was created bash script (`train.sh`). At the beggining is created `bg.txt` file which contains paths for all `negatives`:
```bash
find neg/ -iname "*.jpg" > bg.txt
```
Content of `bg.txt` look like this:
```
...
neg/404.jpg
neg/1727.jpg
neg/1202.jpg
neg/1359.jpg
...
```
Next few variables are defined, `data/` folder is created and proper training is taking place using `opencv_traincascade` commmand:
```bash
STAGES=$1  # amount of training stages
DIM=$2  # same as in generate_vector.sh script
FA_RATE=$3  # false alarm rate, the smaller the longer training process will be and classifier will be beter 

NUM_POS=800  # number of positives that will be investigated in each training stage (usually 80-90% of all positives)
NUM_NEG=400  # half of NUM_POS

mkdir data
opencv_traincascade -data data -vec positives.vec -bg bg.txt -numPos $NUM_POS -numNeg $NUM_NEG -numStages $STAGES -w $DIM -h $DIM -maxFalseAlarmRate  $FA_RATE
```
After executing this script `data/` folder will be visible with data from all stages and main classifier in `cascade.xml` file:
```
$ root@vm1:~/home/github/tennis-ball-detector/data# ls -l
total 20
-rw-r--r-- 1 root root 5657 Apr  4 12:16 cascade.xml
-rw-r--r-- 1 root root  594 Apr  4 12:16 params.xml
-rw-r--r-- 1 root root 1461 Apr  4 12:16 stage0.xml
-rw-r--r-- 1 root root 1463 Apr  4 12:16 stage1.xml
```

# Testing
Run:
```
$ chmod 777 train.sh
$ chmod 777 generate_vector.sh
$ ./generate_vector.sh 22
$ ./train.sh 12 22 0.25
```
For testing classifier quality was created `detector.py` script which takes two arguments - path to directory where images for tennis balls detection are stored and path to classifier:
```
$ python3 detector.py images/ data/cascade.xml
```
Directory `results` will be created that contains images from `images` with tennis balls marked in green squares and text files with detail info about detected balls.  

Image:
<p align="center">
  <img src="https://github.com/radosz99/tennis-ball-detector/blob/main/results/8.jpg" width=60% alt="Img"/> 
</p> 

Text file:
```
ball_no_0: coords (585, 12), size 56x56
ball_no_1: coords (115, 241), size 72x72
ball_no_2: coords (96, 296), size 71x71
ball_no_3: coords (629, 279), size 79x79
ball_no_4: coords (178, 129), size 57x57
```
You can test classifier from `classifiers/` directory created using parameters `STAGES=12`, `DIM=24`, `FA_RATE=0.25`:
```
python detector.py images/ classifiers/cascade_12stages_24dim_0_25far.xml
```

# References
<a id="1">[1]</a> 
`libopencv-dev` Ubuntu documentation
http://manpages.ubuntu.com/manpages/xenial/man1/opencv_createsamples.1.html

<a id="2">[2]</a> 
Creating your own Haar Cascade OpenCV Python Tutorial
https://pythonprogramming.net/haar-cascade-object-detection-python-opencv-tutorial/
