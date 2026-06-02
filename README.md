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
- Unit tests with Catch2 and CTest.
- Cross-platform GitHub Actions CI for Linux, Windows, and macOS.
- Docker build/test/package environment.
- Release packaging through CMake install rules and helper scripts.

Still planned:

- UI visual polish.
- Screenshots and documentation polish.
- Static analysis hardening.
- Optional Docker GUI runner.
- Optional gameplay additions such as ghost piece, hold piece, and persistent high score.

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

For a clean build, remove generated preset directories and configure again:

```bash
rm -rf build/debug build/release dist
cmake --preset debug
cmake --build --preset debug
```

On Windows PowerShell:

```powershell
Remove-Item -Recurse -Force build/debug, build/release, dist -ErrorAction SilentlyContinue
cmake --preset debug
cmake --build --preset debug
```

## Testing

Tests are enabled by default through `TET_RAY_GAME_BUILD_TESTS=ON`. Configure, build, and run them with:

```bash
cmake --preset debug
cmake --build --preset debug
ctest --test-dir build/debug --output-on-failure
```

The test target is `tet_ray_game_tests` and links against `tet_ray_game_core` plus Catch2. The core boundary check keeps `src/core` independent from Raylib:

```bash
bash scripts/check-core-boundary.sh
```

## Continuous Integration

GitHub Actions runs Debug configure/build/test and Release configure/build/install on:

- `ubuntu-latest`
- `windows-latest`
- `macos-latest`

The Ubuntu job also runs `scripts/check-core-boundary.sh`. CI uses Ninja through `CMAKE_GENERATOR=Ninja` and installs the platform dependencies needed for Raylib builds.

## Docker Build Environment

Build the Docker image:

```bash
docker build -t tet-ray-game-builder .
```

Run the full build/test/package workflow in the container:

```bash
docker run --rm -v "$PWD:/workspace" -w /workspace tet-ray-game-builder
```

Or use Compose:

```bash
docker compose up --build builder
```

The Docker workflow is intended for build, tests, and release packaging. It does not run the graphical game window.
Inside the container, builds use `build/docker-debug` and `build/docker-release` to avoid clashing with host preset build directories.

## Release Packaging

Create a release layout with CMake directly:

```bash
cmake --preset release
cmake --build --preset release
cmake --install build/release --prefix dist
```

Or use the helper scripts:

```bash
bash scripts/package-release.sh
```

On Windows PowerShell:

```powershell
./scripts/package-release.ps1
```

The generated `dist/` directory contains the executable, `assets/fonts`, `assets/sounds`, and `README.md`.

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
|-- .github/
|   `-- workflows/
|-- scripts/
|-- src/
|   |-- app/
|   |-- assets/
|   |-- audio/
|   |-- core/
|   |-- input/
|   `-- rendering/
|-- tests/
|-- CMakeLists.txt
|-- CMakePresets.json
`-- README.md
```

## Roadmap

- UI visual polish.
- Screenshots and documentation polish.
- Static analysis hardening.
- Optional Docker GUI runner.
- Optional ghost piece, hold piece, and persistent high score.
