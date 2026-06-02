# TetRay Game

[![CI](https://github.com/dimbo1324/tet-ray-game-t/actions/workflows/ci.yml/badge.svg)](https://github.com/dimbo1324/tet-ray-game-t/actions/workflows/ci.yml)

Modern C++23 / Raylib Tetris game with portable CMake, Catch2 tests, GitHub Actions CI, Docker build environment, release packaging, and a Raylib-free gameplay core.

## Features

- Classic Tetris gameplay with all 7 tetrominoes.
- 7-bag randomizer.
- Pause/resume, hard drop, and soft drop scoring.
- Level and speed progression.
- Next piece preview.
- Score, level, and lines display.
- Music and sound effects.
- Polished Raylib UI with readable panels and pause/game-over overlays.
- Portable CMake presets.
- Catch2 and CTest coverage for core gameplay logic.
- GitHub Actions CI across Linux, Windows, and macOS.
- Docker build/test/package environment.
- CMake install rules and release packaging scripts.
- Optional compiler warnings, sanitizers, clang-tidy, and cppcheck support.

## Tech Stack

- C++23
- Raylib
- CMake
- Catch2
- CTest
- Docker / Docker Compose
- GitHub Actions

## Project Structure

```text
.
|-- assets/
|   |-- fonts/
|   `-- sounds/
|-- docs/
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
|-- Dockerfile
`-- docker-compose.yml
```

## Quick Start

Configure and build Debug:

```bash
cmake --preset debug
cmake --build --preset debug
```

Run the executable from the build directory:

```bash
cd build/debug
./tet_ray_game_app
```

On Windows PowerShell:

```powershell
cd build/debug
./tet_ray_game_app.exe
```

The build copies `assets/` next to the executable.

## Tests

```bash
cmake --preset debug
cmake --build --preset debug
ctest --test-dir build/debug --output-on-failure
```

The `tet_ray_game_tests` target links to `tet_ray_game_core` and Catch2. The gameplay core is intentionally Raylib-free, so logic tests run headlessly.

## Docker

Build the builder image:

```bash
docker build -t tet-ray-game-builder .
```

Run the build/test/package workflow:

```bash
docker compose run --rm builder
```

The default Docker flow is for building, testing, and packaging. It does not run the game window. An experimental Linux X11 runner is documented in [docs/docker.md](docs/docker.md).

## Release Package

Use the helper scripts:

```bash
./scripts/package-release.sh
```

On Windows PowerShell:

```powershell
./scripts/package-release.ps1
```

Or run CMake directly:

```bash
cmake --preset release
cmake --build --preset release
cmake --install build/release --prefix dist
```

Expected layout:

```text
dist/
|-- tet_ray_game_app(.exe)
|-- assets/
|   |-- fonts/
|   `-- sounds/
`-- README.md
```

## Controls

- Left / Right: move.
- Up: rotate.
- Down: soft drop.
- Space: hard drop while running; restart on game over.
- P or Escape: pause/resume.
- Enter: restart on game over.

## Architecture

- `src/core` owns gameplay state and rules and does not include Raylib.
- `src/rendering`, `src/audio`, `src/input`, and `src/assets` are adapter layers.
- `src/app` wires the core and adapters into the Raylib loop.
- Tests target the core logic first, keeping CI headless and portable.

More detail: [docs/architecture.md](docs/architecture.md).

## Quality

- Catch2 tests are discovered through CTest.
- CI builds Debug and Release on Linux, Windows, and macOS.
- A core boundary script checks that Raylib does not leak into `src/core`.
- Project warnings are enabled by default for project targets.
- Warnings-as-errors, sanitizers, and clang-tidy are available as opt-in CMake options.
- cppcheck commands are documented and scripted for local use.

See [docs/testing.md](docs/testing.md) and [docs/building.md](docs/building.md).

## Screenshots

No committed gameplay screenshot is included yet. See [docs/screenshots/README.md](docs/screenshots/README.md) for the recommended screenshot set.

## Assets And Credits

- Raylib is used through CMake FetchContent.
- Fonts under `assets/fonts/` include their OFL license files.
- Sound and music files are bundled project assets. Verify their provenance before commercial redistribution.

See [docs/assets-and-licenses.md](docs/assets-and-licenses.md).

## License

No root `LICENSE` file is present yet. Add a project license before public redistribution.

## Roadmap

Completed:

- C++23 baseline.
- Portable CMake and asset layout.
- Raylib-free gameplay core.
- Gameplay polish: 7-bag, pause, hard drop, scoring, levels.
- Catch2/CTest test suite.
- Cross-platform CI.
- Docker build environment.
- Release packaging.
- UI polish.
- GitHub-ready documentation.
- Static analysis and hardening configuration.

Future:

- Ghost piece.
- Hold piece.
- High score persistence.
- Settings and key remapping.
- WebAssembly build.
- Installer packages.
- Optional Docker GUI/noVNC runner.
