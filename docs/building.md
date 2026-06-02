# Building

## Requirements

- CMake 3.28 or newer.
- A C++23 compiler.
- Git.
- Internet access for the first FetchContent download of Raylib and Catch2.

Linux builds also need X11/OpenGL/audio development libraries for Raylib. See [docker.md](docker.md) for the Ubuntu package list used by CI and Docker.

## Debug

```bash
cmake --preset debug
cmake --build --preset debug
```

## Release

```bash
cmake --preset release
cmake --build --preset release
```

Release application build without test targets:

```bash
cmake --preset release-no-tests
cmake --build --preset release-no-tests
```

Core/tests-only build without the Raylib app:

```bash
cmake -S . -B build/core-tests -DTET_RAY_GAME_BUILD_APP=OFF -DTET_RAY_GAME_BUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build/core-tests
ctest --test-dir build/core-tests --output-on-failure
```

## Clean Build

```bash
rm -rf build/debug build/release dist
cmake --preset debug
cmake --build --preset debug
```

PowerShell:

```powershell
Remove-Item -Recurse -Force build/debug, build/release, dist -ErrorAction SilentlyContinue
cmake --preset debug
cmake --build --preset debug
```

## Quality Options

Project warnings are enabled by default:

```bash
cmake --preset debug -DTET_RAY_GAME_ENABLE_WARNINGS=ON
```

Warnings-as-errors are available but off by default:

```bash
cmake --preset debug -DTET_RAY_GAME_WARNINGS_AS_ERRORS=ON
```

Sanitizers are available for GCC/Clang non-MSVC builds:

```bash
cmake --preset debug-sanitize
cmake --build --preset debug-sanitize
ctest --test-dir build/debug-sanitize --output-on-failure
```

clang-tidy integration is opt-in:

```bash
cmake --preset debug-clang-tidy
cmake --build --preset debug-clang-tidy
```

If `clang-tidy` is not installed, CMake warns but does not fail.

`TET_RAY_GAME_BUILD_APP=OFF` keeps Raylib out of configure/build for headless core test runs.

## Platform Notes

- Windows: MSVC, Clang, or another C++23 compiler should work. Ninja is used by CI.
- Linux: install X11/OpenGL/audio development packages before configuring.
- macOS: install CMake and Ninja if you want to mirror CI.
