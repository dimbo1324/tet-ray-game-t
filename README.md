# Tet-Ray-Game

Modern C++23 Tetris game built with Raylib and portable CMake.

## Project Description

Tet-Ray-Game is a classic Tetris-style game implemented in C++. The gameplay model lives in a Raylib-free core layer, while rendering, audio, input, assets, and the application shell are adapter layers around it.

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
- Domain model cleanup with safer tetromino identity.
- 7-bag tetromino generation.
- Pause/resume.
- Hard drop.
- Soft and hard drop scoring.
- Level and speed progression.

Planned:

- Unit tests.
- CI.
- Docker build.
- Release packaging.
- UI visual polish.
- Static analysis.

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

## Controls

- Left arrow: move left.
- Right arrow: move right.
- Down arrow: soft drop.
- Up arrow: rotate.
- Space: hard drop while running.
- P or Escape: pause/resume.
- Enter: restart after game over.
- Space: restart after game over.

## Architecture

- `src/core` contains gameplay state and rules. It does not include Raylib and is intended to be testable without opening a window.
- `src/core` owns `TetrominoType`, `GameStatus`, `RandomBag`, and `ScoreSystem`.
- `src/rendering` contains Raylib drawing code, colors, UI panels, grid/block drawing, pause/game-over overlays, and text rendering.
- `src/audio` owns Raylib music and sound resources.
- `src/input` maps Raylib keyboard input to game actions.
- `src/assets` resolves runtime asset paths.
- `src/app` wires the core and adapters into the game loop.

## Gameplay Rules

- Pieces use a 7-bag: every bag contains one each of I, J, L, O, S, T, and Z before reshuffling.
- `GameStatus` tracks Running, Paused, and GameOver.
- While paused, movement, rotation, soft drop, hard drop, and automatic falling are ignored. Music currently continues.
- Line clear scoring is `100/300/500/800 * level` for 1/2/3/4 lines.
- Soft drop gives `+1` per manually dropped cell.
- Hard drop gives `+2` per dropped cell and locks immediately.
- Level is `(total lines cleared / 10) + 1`.
- Drop interval starts at `0.5s`, decreases by `0.04s` per level, and is clamped to `0.08s`.

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

- Tests.
- CI.
- Docker.
- Release packaging.
- UI visual polish.
- Static analysis.
