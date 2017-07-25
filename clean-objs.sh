#!/bin/bash
echo "Linux clean makefile target"
cd script//linux
make clean
cd ../../logs
rm *.log
echo "Cleaned objs."
echo "Have a nice day."
