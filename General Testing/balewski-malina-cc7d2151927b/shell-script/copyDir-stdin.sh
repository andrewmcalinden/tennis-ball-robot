#!/bin/sh
path1=/Volumes/EXCHANGE/transfer
path2=/Volumes/EXCHANGE/final
id=0
while [ true ]; do
    read line
    if [ $? -ne 0 ]; then break; fi
    echo "LINE IS " $line    
    inpFull=$path1/$line/"********  raw negatives/"
    outFull=$path2/$line/
   
    ls "$inpFull"
    mkdir "$outFull"
    cd "$inpFull"
    mv * "$outFull"
    cd -

    id=$[ $id + 1 ]
    #break
done

echo "info: $id copied"