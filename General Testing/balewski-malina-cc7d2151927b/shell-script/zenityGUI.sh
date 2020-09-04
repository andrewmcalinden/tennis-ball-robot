#!/bin/bash
dir=$(zenity --file-selection --directory)
wget -O $dir/test.txt "https://www.dropbox.com/s/mx9eqve5l2ipgyk/test.txt?dl=1"