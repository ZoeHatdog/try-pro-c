# Pro-C Build Script for Windows PowerShell - Database Query Service
# Builds a service executable that accepts JSON input and returns JSON output

$ErrorActionPreference = "Stop"

# Check if ORACLE_HOME is set
if (-not $env:ORACLE_HOME) {
    Write-Host "ORACLE_HOME not set. Setting default..." -ForegroundColor Yellow
    $env:ORACLE_HOME = "C:\oracle\instantclient_21_13\instantclient_23_0"
}

# Set PATH to include Oracle directories
$env:PATH = "$env:ORACLE_HOME;$env:ORACLE_HOME\sdk;$env:PATH"

# Set paths
$procExe = Join-Path $env:ORACLE_HOME "sdk\proc.exe"
$procExeBin = Join-Path $env:ORACLE_HOME "bin\proc.exe"
$sdkInclude = Join-Path $env:ORACLE_HOME "sdk\include"
$sdkLib = $env:ORACLE_HOME
$srcInclude = Join-Path $PSScriptRoot "src\include"

# Find proc.exe
if (Test-Path $procExe) {
    $procPath = $procExe
} elseif (Test-Path $procExeBin) {
    $procPath = $procExeBin
} else {
    Write-Host "Error: proc.exe not found!" -ForegroundColor Red
    Write-Host "Searched: $procExe" -ForegroundColor Red
    Write-Host "Searched: $procExeBin" -ForegroundColor Red
    exit 1
}

Write-Host "Building Pro-C Database Query Service..." -ForegroundColor Green
Write-Host "ORACLE_HOME: $env:ORACLE_HOME" -ForegroundColor Cyan

# Navigate to project root
Set-Location $PSScriptRoot

# Precompile Pro-C files
Write-Host ""
Write-Host "Precompiling Pro-C files..." -ForegroundColor Yellow

$files = @(
    @{Input="src\db\connection.pc"; Output="src\db\connection.c"},
    @{Input="src\db\query_runner.pc"; Output="src\db\query_runner.c"},
    @{Input="src\db_query_service.pc"; Output="src\db_query_service.c"}
)

foreach ($file in $files) {
    Write-Host "  Processing $($file.Input)..." -ForegroundColor Gray
    $inputPath = Join-Path $PSScriptRoot $file.Input
    $outputPath = Join-Path $PSScriptRoot $file.Output
    
    # Build argument string for proc.exe
    $procArgs = "iname=$inputPath oname=$outputPath mode=ansi lines=yes parse=partial include=`"$sdkInclude`" include=`"$srcInclude`""
    
    try {
        & $procPath $procArgs.Split(' ') 2>&1 | Out-File "$outputPath.log" -Encoding utf8
        $exitCode = $LASTEXITCODE
        
        # Check if output file was created
        $fileCreated = Test-Path $outputPath
        
        if (-not $fileCreated) {
            Write-Host "Error precompiling $($file.Input)!" -ForegroundColor Red
            if (Test-Path "$outputPath.log") {
                $logContent = Get-Content "$outputPath.log" -ErrorAction SilentlyContinue
                if ($logContent) {
                    Write-Host "Log output (last 10 lines):" -ForegroundColor Yellow
                    $logContent | Select-Object -Last 10 | Write-Host -ForegroundColor Yellow
                }
            }
            exit 1
        } else {
            Write-Host "    Success" -ForegroundColor Green
        }
    } catch {
        Write-Host "Exception: $_" -ForegroundColor Red
        exit 1
    }
}

Write-Host "Precompilation successful!" -ForegroundColor Green

# Compile C files
Write-Host ""
Write-Host "Compiling C files..." -ForegroundColor Yellow

$gccPath = "C:\Users\arnel\Downloads\winlibs-x86_64-posix-seh-gcc-15.2.0-mingw-w64ucrt-13.0.0-r5\mingw64\bin\gcc.exe"

if (-not (Test-Path $gccPath)) {
    Write-Host "Error: gcc not found at: $gccPath" -ForegroundColor Red
    exit 1
}

$gccArgs = @(
    "-I$sdkInclude",
    "-I$srcInclude",
    "-g",
    "-c",
    "-fcommon"
)

$objectFiles = @()

foreach ($file in $files) {
    $cFile = Join-Path $PSScriptRoot $file.Output
    $oFile = $cFile -replace '\.c$', '.o'
    $objectFiles += $oFile
    
    Write-Host "  Compiling $($file.Output)..." -ForegroundColor Gray
    
    $compileArgs = $gccArgs + @($cFile, "-o", $oFile)
    
    try {
        $process = Start-Process -FilePath $gccPath -ArgumentList $compileArgs -Wait -NoNewWindow -PassThru
        
        if ($process.ExitCode -ne 0) {
            Write-Host "Error compiling $($file.Output)!" -ForegroundColor Red
            exit 1
        }
    } catch {
        Write-Host "Exception: $_" -ForegroundColor Red
        exit 1
    }
}

Write-Host "Compilation successful!" -ForegroundColor Green

# Link executable
Write-Host ""
Write-Host "Linking executable..." -ForegroundColor Yellow

$serviceExe = Join-Path $PSScriptRoot "db_query_service.exe"

$linkArgs = @(
    $objectFiles
    "-o", $serviceExe,
    "-L$sdkLib",
    "-loci"
)

Write-Host "  Linking command: $gccPath $($linkArgs -join ' ')" -ForegroundColor DarkGray

try {
    $process = Start-Process -FilePath $gccPath -ArgumentList $linkArgs -Wait -NoNewWindow -PassThru
    
    if ($process.ExitCode -ne 0) {
        Write-Host "Error linking executable!" -ForegroundColor Red
        exit 1
    }
} catch {
    Write-Host "Exception: $_" -ForegroundColor Red
    exit 1
}

Write-Host ""
Write-Host "Build completed successfully!" -ForegroundColor Green
Write-Host "Service executable: db_query_service.exe" -ForegroundColor Cyan
Write-Host "Usage: echo '{\"sql\":\"SELECT ...\",\"binds\":{...}}' | .\db_query_service.exe" -ForegroundColor Cyan


