$ErrorActionPreference = "Stop"

if (-not (Get-Command cppcheck -ErrorAction SilentlyContinue)) {
    Write-Error "cppcheck was not found. Install cppcheck or run this script in an environment that provides it."
}

cppcheck --enable=warning,style,performance,portability --std=c++23 --suppress=missingIncludeSystem src tests
