#!/bin/bash

STAGES=$1
DIM=$2
FA_RATE=$3

NUM_POS=800
NUM_NEG=400

find neg -iname "*.jpg" > bg.txt
rm -rf data
mkdir data
opencv_traincascade -data data -vec positives.vec -bg bg.txt -numPos $NUM_POS -numNeg $NUM_NEG -numStages $STAGES -w $DIM -h $DIM -maxFalseAlarmRate  $FA_RATE
rm -rf all
rm positives.vec
rm bg.txt

