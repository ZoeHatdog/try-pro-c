@echo off
REM Wrapper script to run build.ps1 with proper execution policy
powershell -ExecutionPolicy Bypass -File "%~dp0build.ps1"
if errorlevel 1 (
    pause
    exit /b 1
)

