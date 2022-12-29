@echo off
set name=BlenderBatch
title Compiling %name%
color 7
gcc *.c "resources\icon\icon.res" -Wall -O2 -o "%name%.exe"
title DONE!
echo.
pause