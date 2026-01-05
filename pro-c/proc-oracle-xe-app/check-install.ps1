# Check Oracle Instant Client Installation
$oracleHome = "C:\oracle\instantclient_21_13"

Write-Host "=== Oracle Instant Client Installation Check ===" -ForegroundColor Cyan
Write-Host ""

# Check 1: Directory structure
Write-Host "1. Directory Structure:" -ForegroundColor Yellow
Get-ChildItem $oracleHome | Select-Object Name, PSIsContainer | Format-Table -AutoSize

# Check 2: Look for proc.exe
Write-Host "`n2. Looking for proc.exe..." -ForegroundColor Yellow
$procExe = Get-ChildItem -Path $oracleHome -Recurse -Filter "proc.exe" -ErrorAction SilentlyContinue
if ($procExe) {
    Write-Host "   [OK] Found proc.exe at:" -ForegroundColor Green
    $procExe | ForEach-Object { Write-Host "      $($_.FullName)" -ForegroundColor Gray }
} else {
    Write-Host "   [FAIL] proc.exe NOT found" -ForegroundColor Red
}

# Check 3: Look for SDK directory
Write-Host "`n3. Looking for SDK directory..." -ForegroundColor Yellow
$sdkDirs = Get-ChildItem -Path $oracleHome -Recurse -Directory -Filter "sdk" -ErrorAction SilentlyContinue
if ($sdkDirs) {
    Write-Host "   [OK] Found SDK directory:" -ForegroundColor Green
    $sdkDirs | ForEach-Object { 
        Write-Host "      $($_.FullName)" -ForegroundColor Gray
        Write-Host "      Contents:" -ForegroundColor DarkGray
        Get-ChildItem $_.FullName | Select-Object -First 10 Name | ForEach-Object { Write-Host "        - $($_.Name)" -ForegroundColor DarkGray }
    }
} else {
    Write-Host "   [FAIL] SDK directory NOT found" -ForegroundColor Red
}

# Check 4: Look for sqlca.h
Write-Host "`n4. Looking for sqlca.h..." -ForegroundColor Yellow
$sqlca = Get-ChildItem -Path $oracleHome -Recurse -Filter "sqlca.h" -ErrorAction SilentlyContinue
if ($sqlca) {
    Write-Host "   [OK] Found sqlca.h at:" -ForegroundColor Green
    $sqlca | ForEach-Object { Write-Host "      $($_.FullName)" -ForegroundColor Gray }
} else {
    Write-Host "   [FAIL] sqlca.h NOT found" -ForegroundColor Red
}

# Check 5: Look for mesg directory
Write-Host "`n5. Looking for mesg directory..." -ForegroundColor Yellow
$mesgDirs = Get-ChildItem -Path $oracleHome -Recurse -Directory -Filter "mesg" -ErrorAction SilentlyContinue
if ($mesgDirs) {
    Write-Host "   [OK] Found mesg directory:" -ForegroundColor Green
    $mesgDirs | ForEach-Object { 
        Write-Host "      $($_.FullName)" -ForegroundColor Gray
        $msgFiles = Get-ChildItem $_.FullName -ErrorAction SilentlyContinue
        if ($msgFiles) {
            Write-Host "      Message files found: $($msgFiles.Count)" -ForegroundColor Green
            $msgFiles | Select-Object -First 5 Name | ForEach-Object { Write-Host "        - $($_.Name)" -ForegroundColor DarkGray }
        }
    }
} else {
    Write-Host "   [FAIL] mesg directory NOT found" -ForegroundColor Red
}

# Check 6: Look for .msb or .msg files
Write-Host "`n6. Looking for message files (.msb/.msg)..." -ForegroundColor Yellow
$msbFiles = Get-ChildItem -Path $oracleHome -Recurse -Filter "*.msb" -ErrorAction SilentlyContinue
$msgFiles = Get-ChildItem -Path $oracleHome -Recurse -Filter "*.msg" -ErrorAction SilentlyContinue
if ($msbFiles) {
    Write-Host "   [OK] Found $($msbFiles.Count) .msb files" -ForegroundColor Green
    $msbFiles | Select-Object -First 5 FullName | ForEach-Object { Write-Host "      $($_.FullName)" -ForegroundColor Gray }
} elseif ($msgFiles) {
    Write-Host "   [OK] Found $($msgFiles.Count) .msg files" -ForegroundColor Green
    $msgFiles | Select-Object -First 5 FullName | ForEach-Object { Write-Host "      $($_.FullName)" -ForegroundColor Gray }
} else {
    Write-Host "   [FAIL] No message files found" -ForegroundColor Red
}

# Summary
Write-Host "`n=== Summary ===" -ForegroundColor Cyan
$hasProc = [bool]$procExe
$hasSdk = [bool]$sdkDirs
$hasSqlca = [bool]$sqlca
$hasMesg = [bool]$mesgDirs -or [bool]$msbFiles -or [bool]$msgFiles

if ($hasProc -and $hasSdk -and $hasSqlca) {
    Write-Host "Installation Status: " -NoNewline
    if ($hasMesg) {
        Write-Host "[COMPLETE]" -ForegroundColor Green
        Write-Host "All required components are present!" -ForegroundColor Green
    } else {
        Write-Host "[PARTIAL]" -ForegroundColor Yellow
        Write-Host "Core components present, but message files missing." -ForegroundColor Yellow
        Write-Host "This may cause PCC-F-NOERRFILE error, but compilation might still work." -ForegroundColor Yellow
    }
} else {
    Write-Host "Installation Status: " -NoNewline
    Write-Host "[INCOMPLETE]" -ForegroundColor Red
    Write-Host "Missing required components. Please extract all 3 packages:" -ForegroundColor Red
    Write-Host "  1. instantclient-basic-windows.x64-*.zip" -ForegroundColor Yellow
    Write-Host "  2. instantclient-sdk-windows.x64-*.zip" -ForegroundColor Yellow
    Write-Host "  3. instantclient-precomp-windows.x64-*.zip" -ForegroundColor Yellow
    Write-Host "All to the same directory: $oracleHome" -ForegroundColor Yellow
}

