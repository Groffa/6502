@echo off

set MYVC=C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build

call "%MYVC%\vcvars64.bat"

REM cl /Fe6502.exe /O2 6502.cpp
cl /Zi /Fe6502_debug.exe 6502.cpp