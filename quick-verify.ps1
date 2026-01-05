# Quick Verification Script
Write-Host "=== Quick Service Verification ===" -ForegroundColor Cyan
Write-Host ""

# 1. Backend
Write-Host "1. Backend Server..." -NoNewline
try {
    $response = Invoke-WebRequest -Uri "http://localhost:5000/health" -UseBasicParsing -TimeoutSec 2 -ErrorAction Stop
    Write-Host " [OK]" -ForegroundColor Green
} catch {
    Write-Host " [FAIL]" -ForegroundColor Red
}
Write-Host ""

# 2. Frontend
Write-Host "2. Frontend Server..." -NoNewline
try {
    $response = Invoke-WebRequest -Uri "http://localhost:3000" -UseBasicParsing -TimeoutSec 2 -ErrorAction Stop
    Write-Host " [OK]" -ForegroundColor Green
} catch {
    Write-Host " [FAIL]" -ForegroundColor Red
}
Write-Host ""

# 3. Oracle Port
Write-Host "3. Oracle Database Port 1521..." -NoNewline
$portTest = Test-NetConnection -ComputerName localhost -Port 1521 -WarningAction SilentlyContinue -InformationLevel Quiet
if ($portTest) {
    Write-Host " [OK]" -ForegroundColor Green
} else {
    Write-Host " [FAIL]" -ForegroundColor Red
}
Write-Host ""

# 4. Pro-C App
Write-Host "4. Pro-C Application..." -NoNewline
$appPath = "pro-c\proc-oracle-xe-app\app.exe"
if (Test-Path $appPath) {
    Write-Host " [OK]" -ForegroundColor Green
} else {
    Write-Host " [NOT FOUND]" -ForegroundColor Yellow
}
Write-Host ""

Write-Host "=== Access URLs ===" -ForegroundColor Cyan
Write-Host "Frontend: http://localhost:3000" -ForegroundColor White
Write-Host "Backend:  http://localhost:5000" -ForegroundColor White
Write-Host "Health:   http://localhost:5000/health" -ForegroundColor White
Write-Host "Oracle:   localhost:1521/XE" -ForegroundColor White
Write-Host ""

