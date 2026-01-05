# Test if proc.exe works despite missing message files
$oracleHome = "C:\oracle\instantclient_21_13\instantclient_23_0"

# Set environment variables in current session
$env:ORACLE_HOME = $oracleHome
$env:PATH = "$oracleHome;$oracleHome\sdk;$env:PATH"

$testInput = "C:\Users\arnel\Downloads\Side-Projects\try-pro-c\pro-c\proc-oracle-xe-app\src\main.pc"
$testOutput = "C:\Users\arnel\Downloads\Side-Projects\try-pro-c\pro-c\proc-oracle-xe-app\src\main_test.c"

# Remove test output if exists
if (Test-Path $testOutput) { 
    Remove-Item $testOutput 
    Write-Host "Removed existing test file" -ForegroundColor Gray
}

Write-Host "Testing proc.exe..." -ForegroundColor Yellow
Write-Host "ORACLE_HOME: $env:ORACLE_HOME" -ForegroundColor Cyan
Write-Host "Input: $testInput" -ForegroundColor Gray
Write-Host "Output: $testOutput" -ForegroundColor Gray
Write-Host ""

# Run proc.exe directly (not via Start-Process to preserve environment)
$procPath = "$oracleHome\sdk\proc.exe"
$procArgs = "iname=$testInput oname=$testOutput mode=ansi lines=yes parse=partial include=`"$oracleHome\sdk\include`" include=`"C:\Users\arnel\Downloads\Side-Projects\try-pro-c\pro-c\proc-oracle-xe-app\src\include`""

& $procPath $procArgs.Split(' ')
$exitCode = $LASTEXITCODE

Write-Host "Exit code: $exitCode" -ForegroundColor Cyan
Write-Host ""

# Check if output file was created
if (Test-Path $testOutput) {
    $fileSize = (Get-Item $testOutput).Length
    Write-Host "SUCCESS: .c file was created!" -ForegroundColor Green
    Write-Host "File size: $fileSize bytes" -ForegroundColor Green
    Write-Host ""
    Write-Host "First 20 lines of generated file:" -ForegroundColor Cyan
    Get-Content $testOutput -TotalCount 20
} else {
    Write-Host "FAILED: .c file was NOT created" -ForegroundColor Red
    Write-Host "The error is blocking compilation" -ForegroundColor Red
}

