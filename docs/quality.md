# Quality

## Build Targets

- `tet_ray_game_core` contains Raylib-free gameplay code.
- `tet_ray_game_assets` contains resource path resolution that can be tested headlessly.
- `tet_ray_game_app` contains the Raylib desktop application and is controlled by `TET_RAY_GAME_BUILD_APP`.
- `tet_ray_game_tests` contains Catch2 tests and is controlled by `TET_RAY_GAME_BUILD_TESTS`.

## Recommended Local Checks

```bash
cmake --preset debug
cmake --build --preset debug
ctest --test-dir build/debug --output-on-failure
cmake --preset release-no-tests
cmake --build --preset release-no-tests
bash scripts/check-core-boundary.sh
bash scripts/check-readme-links.sh
```

Core/tests-only configure:

```bash
cmake -S . -B build/core-tests -DTET_RAY_GAME_BUILD_APP=OFF -DTET_RAY_GAME_BUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build/core-tests
ctest --test-dir build/core-tests --output-on-failure
```

## Optional Analysis

- `TET_RAY_GAME_ENABLE_SANITIZERS=ON` enables address/undefined sanitizers for GCC/Clang non-MSVC builds.
- `TET_RAY_GAME_ENABLE_CLANG_TIDY=ON` enables clang-tidy when it is installed.
- `scripts/run-cppcheck.ps1` and `scripts/run-cppcheck.sh` run cppcheck when available.

## Repository Checks

- `.editorconfig` documents whitespace conventions.
- `.clang-format` documents C++ formatting defaults.
- `scripts/check-readme-links.*` verifies local README links.
- `scripts/check-core-boundary.sh` keeps Raylib out of `src/core`.
