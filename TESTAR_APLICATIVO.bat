@echo off
setlocal
cd /d "%~dp0"
where cl >nul 2>&1
if errorlevel 1 (
 echo Execute no "x64 Native Tools Command Prompt for VS 2026".
 pause
 exit /b 1
)
call scripts\compilar_motor.bat
if errorlevel 1 exit /b 1
call npm.cmd install
if errorlevel 1 exit /b 1
call npm.cmd run desktop:dev
pause
