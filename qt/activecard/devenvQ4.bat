@echo off

REM ############ Compile Path Environment ##############
call "d:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\bin\vcvars32.bat"

REM ################## WIN32-����ϵͳ���� ####################

set PATHEXT=.COM;.EXE;.BAT;.CMD;.VBS;.VBE;.JS;.JSE;.WSF;.WSH
set PROMPT=TV $P$G

REM ################ ϵͳ���뻷������ #####################

set DEVELOPHOME=E:\Demo\activecard\source
set BINHOME=E:\Demo\activecard\bin

REM ################## ����������������� ################

set QTDIR=D:\Qt\4.7.5
set QMAKESPEC=win32-msvc2008

PATH = %QTDIR%\bin;%QTDIR%\lib;%PATH%

REM ################## WIN32-����̨ ####################

E:
cd %DEVELOPHOME%/

cmd /K