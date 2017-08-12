@echo off

echo "Windows Editor build script."
cd script/windows
make build-editor
make link-editor
pause
echo "build hopefully complete. have a nice day"
