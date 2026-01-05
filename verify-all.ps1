# Verification Script - Check All Services
Write-Host "=== Verifying All Services ===" -ForegroundColor Cyan
Write-Host ""

$allGood = $true

# 1. Check Backend Server
Write-Host "1. Checking Backend Server (port 5000)..." -ForegroundColor Yellow
try {
    $response = Invoke-WebRequest -Uri "http://localhost:5000/health" -Method GET -TimeoutSec 5 -UseBasicParsing -ErrorAction Stop
    if ($response.StatusCode -eq 200) {
        Write-Host "   [OK] Backend server is running" -ForegroundColor Green
        $response.Content | ConvertFrom-Json | Format-List | Out-String | Write-Host -ForegroundColor Gray
    }
} catch {
    Write-Host "   [FAIL] Backend server is not responding" -ForegroundColor Red
    Write-Host "   Error: $($_.Exception.Message)" -ForegroundColor Red
    $allGood = $false
}
Write-Host ""

# 2. Check Frontend Server
Write-Host "2. Checking Frontend Server (port 3000)..." -ForegroundColor Yellow
try {
    $response = Invoke-WebRequest -Uri "http://localhost:3000" -Method GET -TimeoutSec 5 -UseBasicParsing -ErrorAction Stop
    if ($response.StatusCode -eq 200) {
        Write-Host "   [OK] Frontend server is running" -ForegroundColor Green
    }
} catch {
    Write-Host "   [FAIL] Frontend server is not responding" -ForegroundColor Red
    Write-Host "   Error: $($_.Exception.Message)" -ForegroundColor Red
    $allGood = $false
}
Write-Host ""

# 3. Check Oracle Database (Port 1521)
Write-Host "3. Checking Oracle Database (port 1521)..." -ForegroundColor Yellow
$oraclePort = Test-NetConnection -ComputerName localhost -Port 1521 -WarningAction SilentlyContinue
if ($oraclePort.TcpTestSucceeded) {
    Write-Host "   [OK] Oracle database port 1521 is open" -ForegroundColor Green
} else {
    Write-Host "   [FAIL] Oracle database port 1521 is not accessible" -ForegroundColor Red
    $allGood = $false
}
Write-Host ""

# 4. Check Oracle Database Connection (using sqlplus if available)
Write-Host "4. Testing Oracle Database Connection..." -ForegroundColor Yellow
$sqlplusPath = Get-Command sqlplus -ErrorAction SilentlyContinue
if ($sqlplusPath) {
    Write-Host "   Testing with sqlplus..." -ForegroundColor Gray
    $testScript = @"
SET PAGESIZE 0
SET FEEDBACK OFF
SELECT 'Connection successful!' FROM DUAL;
EXIT;
"@
    $testScript | & sqlplus -s system/password@localhost:1521/XE 2>&1 | Out-Null
    if ($LASTEXITCODE -eq 0) {
        Write-Host "   [OK] Oracle database connection successful" -ForegroundColor Green
    } else {
        Write-Host "   [FAIL] Oracle database connection failed" -ForegroundColor Red
        Write-Host "   Try: sqlplus system/password@localhost:1521/XE" -ForegroundColor Gray
        $allGood = $false
    }
} else {
    Write-Host "   [SKIP] sqlplus not found in PATH" -ForegroundColor Yellow
    Write-Host "   Manual test: sqlplus system/password@localhost:1521/XE" -ForegroundColor Gray
}
Write-Host ""

# 5. Check Pro-C Application
Write-Host "5. Checking Pro-C Application..." -ForegroundColor Yellow
$appPath = Join-Path $PSScriptRoot "pro-c\proc-oracle-xe-app\app.exe"
if (Test-Path $appPath) {
    Write-Host "   [OK] Pro-C executable found: app.exe" -ForegroundColor Green
    $appInfo = Get-Item $appPath
    Write-Host "   Size: $($appInfo.Length) bytes" -ForegroundColor Gray
    Write-Host "   Created: $($appInfo.LastWriteTime)" -ForegroundColor Gray
} else {
    Write-Host "   [FAIL] Pro-C executable not found" -ForegroundColor Red
    Write-Host "   Run: cd pro-c/proc-oracle-xe-app; .\build.ps1" -ForegroundColor Gray
    $allGood = $false
}
Write-Host ""

# 6. Check Docker Oracle Container (if using Docker)
Write-Host "6. Checking Docker Oracle Container..." -ForegroundColor Yellow
$dockerAvailable = Get-Command docker -ErrorAction SilentlyContinue
if ($dockerAvailable) {
    $container = docker ps -a --filter "name=oracle-xe" --format "{{.Names}} {{.Status}}" 2>$null
    if ($container) {
        Write-Host "   Docker container status: $container" -ForegroundColor Gray
        if ($container -match "Up") {
            Write-Host "   [OK] Docker Oracle container is running" -ForegroundColor Green
        } else {
            Write-Host "   [INFO] Docker Oracle container exists but is not running" -ForegroundColor Yellow
        }
    } else {
        Write-Host "   [INFO] No Docker Oracle container found (using system Oracle)" -ForegroundColor Yellow
    }
} else {
    Write-Host "   [SKIP] Docker not available" -ForegroundColor Yellow
}
Write-Host ""

# Summary
Write-Host "=== Verification Summary ===" -ForegroundColor Cyan
Write-Host ""
if ($allGood) {
    Write-Host "[SUCCESS] All services are working!" -ForegroundColor Green
    Write-Host ""
    Write-Host "Access your application:" -ForegroundColor Yellow
    Write-Host "  - Frontend: http://localhost:3000" -ForegroundColor White
    Write-Host "  - Backend API: http://localhost:5000" -ForegroundColor White
    Write-Host "  - Backend Health: http://localhost:5000/health" -ForegroundColor White
    Write-Host "  - Oracle Database: localhost:1521/XE" -ForegroundColor White
} else {
    Write-Host "[WARNING] Some services are not working properly" -ForegroundColor Yellow
    Write-Host "Please check the errors above and fix them" -ForegroundColor Yellow
}
Write-Host ""

