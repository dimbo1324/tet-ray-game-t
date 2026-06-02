#!/usr/bin/env bash
set -euo pipefail

if ! command -v cppcheck >/dev/null 2>&1; then
    echo "cppcheck was not found. Install cppcheck or run this script in an environment that provides it." >&2
    exit 1
fi

cppcheck --enable=warning,style,performance,portability --std=c++23 --suppress=missingIncludeSystem src tests
