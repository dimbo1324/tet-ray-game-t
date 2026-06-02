$ErrorActionPreference = "Stop"

$repoRoot = Split-Path -Parent $PSScriptRoot
$distDir = Join-Path $repoRoot "dist"

Set-Location $repoRoot

if (Test-Path $distDir) {
    Remove-Item -Recurse -Force $distDir
}

cmake --preset release-no-tests
cmake --build --preset release-no-tests
cmake --install build/release-no-tests --prefix dist

Write-Host "Release package created at: $distDir"
