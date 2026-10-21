@echo off
setlocal
cd /d "%~dp0"
echo ==========================================
echo  ASG V3 - COMPILAR E GERAR INSTALADOR
 echo ==========================================
where cl >nul 2>&1
if errorlevel 1 (
 echo ERRO: Execute este BAT pelo "x64 Native Tools Command Prompt for VS 2026".
 pause
 exit /b 1
)
where cargo >nul 2>&1
if errorlevel 1 (
 echo ERRO: Rust nao encontrado. Instale em https://rustup.rs/ e reabra o terminal.
 pause
 exit /b 1
)
findstr /C:"__GITHUB_OWNER__" src-tauri\tauri.conf.json >nul
if not errorlevel 1 (
 echo ERRO: Configure GitHub e chave publica com CONFIGURAR_GITHUB.ps1 antes de compilar.
 pause
 exit /b 1
)
call scripts\compilar_motor.bat
if errorlevel 1 goto :fail
call npm.cmd install
if errorlevel 1 goto :fail
call npm.cmd run desktop:build
if errorlevel 1 goto :fail
echo.
echo INSTALADOR GERADO EM: src-tauri\target\release\bundle\nsis\
start "" "%cd%\src-tauri\target\release\bundle\nsis"
pause
exit /b 0
:fail
echo FALHA: verifique o erro exibido acima.
pause
exit /b 1
