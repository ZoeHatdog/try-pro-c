# Pro-C Build Script for Windows PowerShell
# Run with: powershell -ExecutionPolicy Bypass -File .\build.ps1
# Or: .\build.ps1 (if execution policy allows)

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

Write-Host "Building Pro-C application..." -ForegroundColor Green
Write-Host "ORACLE_HOME: $env:ORACLE_HOME" -ForegroundColor Cyan
Write-Host "PROC_EXE: $procPath" -ForegroundColor Cyan

# Navigate to project root
Set-Location $PSScriptRoot

# Precompile Pro-C files
Write-Host ""
Write-Host "Precompiling Pro-C files..." -ForegroundColor Yellow

$files = @(
    @{Input="src\main.pc"; Output="src\main.c"},
    @{Input="src\db\connection.pc"; Output="src\db\connection.c"},
    @{Input="src\db\queries.pc"; Output="src\db\queries.c"}
)

foreach ($file in $files) {
    Write-Host "  Processing $($file.Input)..." -ForegroundColor Gray
    $inputPath = Join-Path $PSScriptRoot $file.Input
    $outputPath = Join-Path $PSScriptRoot $file.Output
    
    # Build argument string for proc.exe (using direct call to preserve environment)
    $procArgs = "iname=$inputPath oname=$outputPath mode=ansi lines=yes parse=partial include=`"$sdkInclude`" include=`"$srcInclude`""
    
    Write-Host "    Command: $procPath $procArgs" -ForegroundColor DarkGray
    
    try {
        # Call proc.exe directly to preserve environment variables
        & $procPath $procArgs.Split(' ') 2>&1 | Out-File "$outputPath.log" -Encoding utf8
        $exitCode = $LASTEXITCODE
        
        # Check if output file was created (this is what matters, not exit code)
        $fileCreated = Test-Path $outputPath
        
        if (-not $fileCreated) {
            Write-Host "Error precompiling $($file.Input)!" -ForegroundColor Red
            Write-Host "Exit code: $exitCode" -ForegroundColor Red
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
            if ($exitCode -ne 0) {
                Write-Host "    Note: proc.exe returned exit code $exitCode but .c file was created" -ForegroundColor DarkGray
            }
        }
    } catch {
        Write-Host "Exception: $_" -ForegroundColor Red
        Write-Host $_.Exception.Message -ForegroundColor Red
        exit 1
    }
}

Write-Host "Precompilation successful!" -ForegroundColor Green

# Compile C files (requires gcc)
Write-Host ""
Write-Host "Compiling C files..." -ForegroundColor Yellow

$gccArgs = @(
    "-I$sdkInclude",
    "-I$srcInclude",
    "-g",
    "-c"
)

$objectFiles = @()

foreach ($file in $files) {
    $cFile = Join-Path $PSScriptRoot $file.Output
    $oFile = $cFile -replace '\.c$', '.o'
    $objectFiles += $oFile
    
    Write-Host "  Compiling $($file.Output)..." -ForegroundColor Gray
    
    $compileArgs = $gccArgs + @($cFile, "-o", $oFile)
    
    # Check if gcc exists
    $gccPath = Get-Command gcc -ErrorAction SilentlyContinue
    if (-not $gccPath) {
        Write-Host "Error: gcc not found in PATH!" -ForegroundColor Red
        Write-Host "Please install MinGW or add gcc to your PATH." -ForegroundColor Yellow
        exit 1
    }
    
    try {
        $process = Start-Process -FilePath "gcc" -ArgumentList $compileArgs -Wait -NoNewWindow -PassThru
        
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

$linkArgs = @(
    $objectFiles
    "-o", "$PSScriptRoot\app.exe",
    "-L$sdkLib",
    "-loci"
)

Write-Host "  Linking command: gcc $($linkArgs -join ' ')" -ForegroundColor DarkGray

try {
    $process = Start-Process -FilePath "gcc" -ArgumentList $linkArgs -Wait -NoNewWindow -PassThru
    
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
Write-Host "Run with: .\app.exe" -ForegroundColor Cyan
