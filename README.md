# Tet-Ray-Game

Modern C++23 Tetris game built with Raylib and portable CMake.

## Project Description

Tet-Ray-Game is a classic Tetris-style game implemented in C++ with Raylib for rendering, input, and audio. The current milestone keeps the gameplay code intact and establishes a portable build baseline for future development.

## Current Status

Implemented:

- Classic Tetris gameplay baseline.
- Raylib rendering and audio.
- Score tracking.
- Next piece preview.
- Game over and restart flow.
- Portable CMake baseline.
- C++23 baseline.

Planned:

- Asset portability improvements.
- Core/rendering separation.
- Unit tests.
- CI.
- Docker build.
- Release packaging.
- UI polish.

## Requirements

- CMake 3.28 or newer.
- A compiler with C++23 support.
- Git.
- Internet connection for the first Raylib FetchContent download.

Potential compiler choices include recent versions of MSVC, GCC, or Clang. Exact platform/compiler support has not yet been fully certified.

## Build Instructions

Configure and build the Debug preset:

```bash
cmake --preset debug
cmake --build --preset debug
```

Configure and build the Release preset:

```bash
cmake --preset release
cmake --build --preset release
```

Raylib is downloaded automatically by CMake through FetchContent on the first configure.

## Run Instructions

After building, the executable is expected in the selected preset build directory:

- Debug: `build/debug/tet_ray_game_app` or `build/debug/tet_ray_game_app.exe`
- Release: `build/release/tet_ray_game_app` or `build/release/tet_ray_game_app.exe`

The build copies `fonts/` and `sounds/` beside the executable. Run the game from the executable directory, for example:

```bash
cd build/debug
./tet_ray_game_app
```

On Windows PowerShell:

```powershell
cd build/debug
./tet_ray_game_app.exe
```

The project still uses simple relative asset paths. A fuller asset-loading layer is planned for a later milestone.

## Repository Hygiene

- Generated build folders and compiler outputs are ignored.
- Use `build/debug` and `build/release` through CMake presets.
- Do not commit generated build directories, CMake caches, binaries, or IDE metadata.

## Project Layout

```text
.
|-- app/
|   |-- blocks/
|   |-- colors/
|   |-- game/
|   |-- grid/
|   |-- positions/
|   `-- main.cpp
|-- fonts/
|-- sounds/
|-- CMakeLists.txt
|-- CMakePresets.json
`-- README.md
```

## Roadmap

- Portable assets.
- Architecture split between core gameplay, rendering, audio, and input.
- Gameplay polish.
- Tests.
- CI.
- Docker.
- Release packaging.
