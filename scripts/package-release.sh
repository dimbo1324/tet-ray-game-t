#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$repo_root"

rm -rf dist

cmake --preset release
cmake --build --preset release
cmake --install build/release --prefix dist

echo "Release package created at: $repo_root/dist"
