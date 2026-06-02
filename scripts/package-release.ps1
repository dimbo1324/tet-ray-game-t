$ErrorActionPreference = "Stop"

$repoRoot = Split-Path -Parent $PSScriptRoot
$distDir = Join-Path $repoRoot "dist"

Set-Location $repoRoot

if (Test-Path $distDir) {
    Remove-Item -Recurse -Force $distDir
}

cmake --preset release
cmake --build --preset release
cmake --install build/release --prefix dist

Write-Host "Release package created at: $distDir"
