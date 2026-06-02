# Contributing

Thanks for helping improve TetRay Game.

## Local Setup

Use a C++23 compiler, CMake 3.28 or newer, Ninja if you want to mirror CI, and Git. Linux builds also need the Raylib system dependencies listed in [docs/docker.md](docs/docker.md).

## Recommended Checks

```bash
cmake --preset debug
cmake --build --preset debug
ctest --test-dir build/debug --output-on-failure
bash scripts/check-core-boundary.sh
bash scripts/check-readme-links.sh
```

On Windows, use the PowerShell README link checker:

```powershell
./scripts/check-readme-links.ps1
```

## Code Style

- Keep gameplay rules in `src/core`.
- Keep Raylib includes out of `src/core`.
- Prefer focused tests for core behavior.
- Use the existing CMake targets and quality options before adding new build structure.
- Keep generated build artifacts out of commits.

## Pull Requests

Include a short summary, the checks you ran, and any known local environment limitations.
