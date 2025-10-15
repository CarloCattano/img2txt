#!/bin/env bash

GREEN='\033[0;32m'
RED='\033[0;31m'
RST='\033[0m'

if [ -f ./img2txt ]; then
    rm ./img2txt
fi

cc main.c -o img2txt -lm

if [ $? -eq 0 ]; then
    printf "\n $GREEN Build successful!$RST" 
else
    printf  "\n$RED Build failed!$RST" 
fi



printf "\nUsage:\n\timg2txt <image.[png/jpg]> [<size>] [--color=256] \n"
printf "\nexample:\n./img2txt zebra.jpg 42 \n"
printf "\n./img2txt zebra.jpg \n"
printf "\n./img2txt zebra.jpg 42 --color=8 # 8-bit color: default its 255 \n"
