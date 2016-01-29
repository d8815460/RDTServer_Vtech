@echo off
if "%NACL_SDK_ROOT%" == "" ( echo Please set NACL_SDK_ROOT enviroment variable to your Native Client SDK root directory)
@%NACL_SDK_ROOT%\tools\make.exe %*
