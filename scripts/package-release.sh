#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$repo_root"

rm -rf dist

cmake --preset release-no-tests
cmake --build --preset release-no-tests
cmake --install build/release-no-tests --prefix dist

echo "Release package created at: $repo_root/dist"
