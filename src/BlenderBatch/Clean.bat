@echo off
rmdir ".vs" /s /q 2> nul
rmdir "x64" /s /q 2> nul
rmdir "BlenderBatch\BlenderBatch" /s /q 2> nul
rmdir "BlenderBatch\x64" /s /q 2> nul
del "BlenderBatch\BlenderBatch.aps" /f 2> nul