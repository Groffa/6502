@echo off

REM set LIBS=user32.lib kernel32.lib gdi32.lib Winmm.lib

set MYVC=C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC

call "%MYVC%\vcvarsall.bat" x64

REM cl /Fe6502.exe /O2 6502.cpp
cl /Zi /Fe6502_debug.exe 6502.cpp
