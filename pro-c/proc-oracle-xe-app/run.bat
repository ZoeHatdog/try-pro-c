@echo off
REM Wrapper script to run run.ps1 with proper execution policy
powershell -ExecutionPolicy Bypass -File "%~dp0run.ps1"
if errorlevel 1 (
    pause
    exit /b 1
)

