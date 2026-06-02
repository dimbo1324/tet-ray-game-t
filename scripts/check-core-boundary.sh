#!/usr/bin/env bash
set -euo pipefail

if grep -RInE 'raylib\.h|Draw[A-Z]|PlaySound|Music|Sound|Font|IsKeyPressed|GetKeyPressed' src/core; then
    echo "src/core must stay independent from Raylib rendering, audio, font, and input APIs." >&2
    exit 1
fi

echo "Core boundary check passed."
