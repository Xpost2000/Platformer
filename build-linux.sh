#!/bin/bash
echo "Linux Build Script"
cd script//linux
make
make link
echo "Build completed without issues hopefully. :)"
echo "Have a nice day."
