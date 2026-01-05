# Run Pro-C Application Script
# Run with: powershell -ExecutionPolicy Bypass -File .\run.ps1
# Or: .\run.ps1 (if execution policy allows)

$ErrorActionPreference = "Stop"

# Set Oracle connection details
if (-not $env:ORACLE_USER) {
    $env:ORACLE_USER = "system"
}
if (-not $env:ORACLE_PASSWORD) {
    $env:ORACLE_PASSWORD = "password"
}
if (-not $env:ORACLE_DATABASE) {
    $env:ORACLE_DATABASE = "localhost:1521/XE"
}

# Navigate to project root
Set-Location $PSScriptRoot

# Check if app exists
$appPath = Join-Path $PSScriptRoot "app.exe"
if (-not (Test-Path $appPath)) {
    Write-Host "Error: app.exe not found!" -ForegroundColor Red
    Write-Host "Please build the application first: .\build.ps1" -ForegroundColor Yellow
    exit 1
}

Write-Host "Running Pro-C application..." -ForegroundColor Green
Write-Host "Database: $env:ORACLE_DATABASE" -ForegroundColor Cyan
Write-Host "User: $env:ORACLE_USER" -ForegroundColor Cyan
Write-Host ""

# Run the application
& $appPath

if ($LASTEXITCODE -eq 0) {
    Write-Host "`nApplication executed successfully." -ForegroundColor Green
} else {
    Write-Host "`nApplication execution failed." -ForegroundColor Red
    exit 1
}