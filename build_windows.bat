@echo off

echo "Windows Build Script"
cd script/windows
make
make link-game
pause
echo "build hopefully complete. have a nice day"
