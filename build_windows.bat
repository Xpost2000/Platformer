@echo off
color 2
echo "Windows Build Script"
cd script/windows
make
make link
cls
color 1
echo "build hopefully complete. have a nice day"
