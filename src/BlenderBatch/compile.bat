@echo off
set name=BlenderBatch
title Compiling %name%
color 7
gcc *.c -Wall -O2 -o "%name%.exe"
title DONE!
echo.
pause