@echo off
setlocal
cd /d "%~dp0.."
where cl >nul 2>&1
if errorlevel 1 (
 echo ERRO: Abra "x64 Native Tools Command Prompt for VS 2026".
 pause
 exit /b 1
)
cmake -S engine -B engine\build -A x64
if errorlevel 1 goto :fail
cmake --build engine\build --config Release --parallel
if errorlevel 1 goto :fail
if not exist "engine\build\Release\asg_engine.exe" goto :fail
echo MOTOR C++ COMPILADO COM SUCESSO
exit /b 0
:fail
echo ERRO NA COMPILACAO DO MOTOR
pause
exit /b 1
