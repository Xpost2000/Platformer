@echo off
color 1
echo "Windows Build Script"
cd script/windows
make
make link
cls
color g
echo "build hopefully complete. have a nice day"
