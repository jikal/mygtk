@echo off

REM ############ Compile Path Environment ##############
call "d:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\bin\vcvars32.bat"

REM ################## WIN32-运行系统变量 ####################

set PATHEXT=.COM;.EXE;.BAT;.CMD;.VBS;.VBE;.JS;.JSE;.WSF;.WSH
set PROMPT=TV $P$G

REM ################ 系统编译环境定义 #####################

set DEVELOPHOME=E:\Demo\activecard\source
set BINHOME=E:\Demo\activecard\bin

REM ################## 第三方软件环境变量 ################

set QTDIR=D:\Qt\4.7.5
set QMAKESPEC=win32-msvc2008

PATH = %QTDIR%\bin;%QTDIR%\lib;%PATH%

REM ################## WIN32-控制台 ####################

E:
cd %DEVELOPHOME%/

cmd /K