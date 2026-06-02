# Testing

The project uses Catch2 v3 through FetchContent and CTest discovery.

## Run Tests

```bash
cmake --preset debug
cmake --build --preset debug
ctest --test-dir build/debug --output-on-failure
```

## Coverage Scope

Current tests cover:

- 7-bag randomizer behavior and deterministic seeds.
- ScoreSystem line, soft drop, and hard drop scoring.
- LevelSystem level/drop interval progression.
- TetrominoType cell-index mapping.
- ResourcePaths asset root, font, and sound path resolution.
- Grid empty state, bounds, cell access, and row clearing.
- Block creation, rotation, undo, and movement.
- Game initial state, pause behavior, drops, reset, and game-over blocking.

## Core Boundary

```bash
bash scripts/check-core-boundary.sh
```

This check keeps `src/core` free from Raylib APIs.

## README Links

```bash
bash scripts/check-readme-links.sh
```

PowerShell:

```powershell
./scripts/check-readme-links.ps1
```

## Static Analysis Helpers

clang-tidy is configured through `.clang-tidy` and the `TET_RAY_GAME_ENABLE_CLANG_TIDY` CMake option.

cppcheck can be run manually:

```bash
./scripts/run-cppcheck.sh
```

PowerShell:

```powershell
./scripts/run-cppcheck.ps1
```
