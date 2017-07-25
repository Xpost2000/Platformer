#!/bin/bash
echo "Linux clean makefile target"
cd script//linux
make clean
cd ../../logs/linux
rm *.log
echo "Cleaned objs."
echo "Have a nice day."
