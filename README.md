# Tet-Ray-Game

Modern C++23 Tetris game built with Raylib and portable CMake.

## Project Description

Tet-Ray-Game is a classic Tetris-style game implemented in C++. The gameplay model now lives in a Raylib-free core layer, while rendering, audio, input, assets, and the application shell are kept as adapter layers around it.

## Current Status

Implemented:

- Classic Tetris gameplay baseline.
- Raylib rendering and audio adapters.
- Score tracking.
- Next piece preview.
- Game over and restart flow.
- Portable CMake baseline.
- C++23 baseline.
- Portable `assets/` runtime layout.
- Core/gameplay split from Raylib-specific code.

Planned:

- Domain cleanup.
- Gameplay MVP polish.
- Unit tests.
- CI.
- Docker build.
- Release packaging.

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

The build copies assets next to the executable:

```text
build/debug/
|-- tet_ray_game_app.exe
`-- assets/
    |-- fonts/
    `-- sounds/
```

Run the game from the executable directory, for example:

```bash
cd build/debug
./tet_ray_game_app
```

On Windows PowerShell:

```powershell
cd build/debug
./tet_ray_game_app.exe
```

## Architecture

- `src/core` contains gameplay state and rules. It does not include Raylib and is intended to be testable without opening a window.
- `src/rendering` contains Raylib drawing code, colors, UI panels, grid/block drawing, and text rendering.
- `src/audio` owns Raylib music and sound resources.
- `src/input` maps Raylib keyboard input to game actions.
- `src/assets` resolves runtime asset paths.
- `src/app` wires the core and adapters into the game loop.

## Assets

Source assets live under:

```text
assets/
|-- fonts/
`-- sounds/
```

CMake copies this directory to `$<TARGET_FILE_DIR:tet_ray_game_app>/assets` after each build.

Runtime asset lookup uses:

- executable directory / `assets`
- current working directory / `assets`
- source-tree development fallback from common build folders

Missing assets are reported to `std::cerr` before Raylib attempts to load them.

## Repository Hygiene

- Generated build folders and compiler outputs are ignored.
- Use `build/debug` and `build/release` through CMake presets.
- Do not commit generated build directories, CMake caches, binaries, or IDE metadata.

## Project Layout

```text
.
|-- assets/
|   |-- fonts/
|   `-- sounds/
|-- src/
|   |-- app/
|   |-- assets/
|   |-- audio/
|   |-- core/
|   |-- input/
|   `-- rendering/
|-- CMakeLists.txt
|-- CMakePresets.json
`-- README.md
```

## Roadmap

- Domain cleanup.
- Gameplay MVP polish.
- Tests.
- CI.
- Docker.
- Release packaging.
