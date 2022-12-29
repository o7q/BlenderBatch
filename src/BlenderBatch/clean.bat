@echo off
set name=BlenderBatch
title Cleaning %name%
color 7
del "%name%.exe" /f 2> nul
rmdir "BlenderBatch" /s /q 2> nul
title DONE!
echo.