# Pro-C Quick Start Guide

## How to Run the Scripts

### Option 1: Use the Batch Files (Easiest)
Simply double-click or run:
```cmd
build.bat
run.bat
```

### Option 2: Run PowerShell Scripts Directly
```powershell
# Set execution policy for current session (if needed)
Set-ExecutionPolicy -ExecutionPolicy Bypass -Scope Process

# Then run the scripts
.\build.ps1
.\run.ps1
```

### Option 3: Run with Explicit Execution Policy
```powershell
powershell -ExecutionPolicy Bypass -File .\build.ps1
powershell -ExecutionPolicy Bypass -File .\run.ps1
```

## Prerequisites

1. **Oracle Instant Client** with Pro-C precompiler installed
2. **GCC compiler** (MinGW or MSYS2)
3. **Oracle XE database** running (via Docker)

## Setup Environment Variables

Before building, set these in PowerShell:
```powershell
$env:ORACLE_HOME = "C:\oracle\instantclient_21_11\instantclient-precomp-windows.x64-21.13.0.0.0dbru\instantclient_21_13"
$env:PATH = "$env:ORACLE_HOME\sdk;$env:ORACLE_HOME\bin;$env:PATH"
$env:ORACLE_USER = "system"
$env:ORACLE_PASSWORD = "password"
$env:ORACLE_DATABASE = "localhost:1521/XE"
```

## Troubleshooting

### "Script cannot be loaded because running scripts is disabled"
**Solution:** Run with execution policy bypass:
```powershell
powershell -ExecutionPolicy Bypass -File .\build.ps1
```

### "proc.exe not found"
**Solution:** Check that ORACLE_HOME is set correctly and proc.exe exists at:
- `%ORACLE_HOME%\sdk\proc.exe` OR
- `%ORACLE_HOME%\bin\proc.exe`

### "gcc not found"
**Solution:** Install MinGW or add gcc to your PATH

### "Cannot connect to database"
**Solution:** 
1. Make sure Oracle XE is running: `docker ps`
2. If not running: `cd docker && docker-compose up -d`
3. Wait 2-3 minutes for Oracle to initialize

