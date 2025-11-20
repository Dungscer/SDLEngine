# ---- CONFIG ----
$SDL2_DIR = "C:\Libraries\SDL2"
$BuildDir = "build"
$VSGenerator = "Visual Studio 17 2022"
$Platform = "x64"

# ---- Ellenőrzés: CMake ----
if (-not (Get-Command cmake -ErrorAction SilentlyContinue)) {
    Write-Host "CMake nincs telepítve vagy nem elérhető a PATH-ban!" -ForegroundColor Red
    exit 1
}

# ---- Build mappa létrehozása ----
if (-not (Test-Path $BuildDir)) {
    New-Item -ItemType Directory -Path $BuildDir
}

Set-Location $BuildDir

# ---- CMake projekt generálása ----
Write-Host "CMake generálás..."
cmake -G "$VSGenerator" -A $Platform -DSDL2_DIR="$SDL2_DIR" ..

if ($LASTEXITCODE -ne 0) { exit 1 }

# ---- Build ----
Write-Host "Buildelés..."
cmake --build . --config Release

if ($LASTEXITCODE -ne 0) { exit 1 }

# ---- SDL2.dll másolása az exe mellé ----
$ExePath = Join-Path -Path (Get-Location) -ChildPath "Release\SDLEngine.exe"
$DllSource = Join-Path -Path $SDL2_DIR -ChildPath "SDL2.dll"
$DllDest = Split-Path $ExePath

Copy-Item $DllSource -Destination $DllDest -Force

Write-Host "Build kész! Az exe elérhető itt: $ExePath"
