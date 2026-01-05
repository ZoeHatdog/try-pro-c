# Start All Services Script
# This script starts: Oracle XE Database, Backend API, and Frontend

Write-Host "=== Starting All Services ===" -ForegroundColor Cyan
Write-Host ""

# Check if Docker is available
$dockerAvailable = Get-Command docker -ErrorAction SilentlyContinue
if (-not $dockerAvailable) {
    Write-Host "Warning: Docker not found in PATH" -ForegroundColor Yellow
    Write-Host "Oracle XE database will not start automatically" -ForegroundColor Yellow
    Write-Host "Please start Docker Desktop and run: cd pro-c/proc-oracle-xe-app/docker && docker-compose up -d" -ForegroundColor Yellow
    Write-Host ""
}

# Step 1: Start Oracle XE Database (if Docker is available)
if ($dockerAvailable) {
    Write-Host "Step 1: Starting Oracle XE Database..." -ForegroundColor Yellow
    $dockerComposePath = Join-Path $PSScriptRoot "pro-c\proc-oracle-xe-app\docker\docker-compose.yml"
    if (Test-Path $dockerComposePath) {
        Push-Location (Join-Path $PSScriptRoot "pro-c\proc-oracle-xe-app\docker")
        docker-compose up -d
        if ($LASTEXITCODE -eq 0) {
            Write-Host "[OK] Oracle XE Database starting..." -ForegroundColor Green
            Write-Host "  Wait 2-3 minutes for Oracle to initialize" -ForegroundColor Gray
        } else {
            Write-Host "[FAIL] Failed to start Oracle XE Database" -ForegroundColor Red
        }
        Pop-Location
    } else {
        Write-Host "[FAIL] docker-compose.yml not found" -ForegroundColor Red
    }
    Write-Host ""
} else {
    Write-Host "Step 1: Skipping Oracle XE (Docker not available)" -ForegroundColor Yellow
    Write-Host ""
}

# Step 2: Start Backend Server
Write-Host "Step 2: Starting Backend Server..." -ForegroundColor Yellow
$backendPath = Join-Path $PSScriptRoot "backend"
if (Test-Path (Join-Path $backendPath "package.json")) {
    Push-Location $backendPath
    
    # Check if node_modules exists
    if (-not (Test-Path "node_modules")) {
        Write-Host "  Installing backend dependencies..." -ForegroundColor Gray
        npm install
    }
    
    # Check if .env exists
    if (-not (Test-Path ".env")) {
        Write-Host "  Creating .env file..." -ForegroundColor Gray
        $envContent = "PORT=5000`nNODE_ENV=development`nFRONTEND_URL=http://localhost:3000`nJWT_SECRET=your-super-secret-jwt-key-change-this-in-production"
        $envContent | Out-File -FilePath ".env" -Encoding utf8 -NoNewline
    }
    
    Write-Host "  Starting backend on port 5000..." -ForegroundColor Gray
    Write-Host "  (Backend will run in background)" -ForegroundColor Gray
    Start-Process powershell -ArgumentList "-NoExit", "-Command", "npm run dev" -WindowStyle Minimized
    Start-Sleep -Seconds 2
    Write-Host "[OK] Backend server started" -ForegroundColor Green
    Pop-Location
} else {
    Write-Host "[FAIL] Backend package.json not found" -ForegroundColor Red
}
Write-Host ""

# Step 3: Start Frontend Server
Write-Host "Step 3: Starting Frontend Server..." -ForegroundColor Yellow
$frontendPath = Join-Path $PSScriptRoot "frontend"
if (Test-Path (Join-Path $frontendPath "package.json")) {
    Push-Location $frontendPath
    
    # Check if node_modules exists
    if (-not (Test-Path "node_modules")) {
        Write-Host "  Installing frontend dependencies..." -ForegroundColor Gray
        npm install
    }
    
    # Check if .env.local exists
    if (-not (Test-Path ".env.local")) {
        Write-Host "  Creating .env.local file..." -ForegroundColor Gray
        "NEXT_PUBLIC_API_URL=http://localhost:5000/api" | Out-File -FilePath ".env.local" -Encoding utf8
    }
    
    Write-Host "  Starting frontend on port 3000..." -ForegroundColor Gray
    Write-Host "  (Frontend will run in background)" -ForegroundColor Gray
    Start-Process powershell -ArgumentList "-NoExit", "-Command", "npm run dev" -WindowStyle Minimized
    Start-Sleep -Seconds 2
    Write-Host "[OK] Frontend server started" -ForegroundColor Green
    Pop-Location
} else {
    Write-Host "[FAIL] Frontend package.json not found" -ForegroundColor Red
}
Write-Host ""

Write-Host "=== All Services Started ===" -ForegroundColor Cyan
Write-Host ""
Write-Host "Services:" -ForegroundColor Yellow
Write-Host "  • Oracle XE Database: localhost:1521/XE" -ForegroundColor White
Write-Host "  • Backend API: http://localhost:5000" -ForegroundColor White
Write-Host "  • Frontend: http://localhost:3000" -ForegroundColor White
Write-Host ""
Write-Host "Note: Oracle XE takes 2-3 minutes to fully initialize" -ForegroundColor Gray
Write-Host "Check Docker Desktop to see Oracle container status" -ForegroundColor Gray
Write-Host ""
Write-Host "To stop services:" -ForegroundColor Yellow
Write-Host "  - Close the PowerShell windows for backend/frontend" -ForegroundColor Gray
Write-Host "  - Run: cd pro-c/proc-oracle-xe-app/docker; docker-compose down" -ForegroundColor Gray

