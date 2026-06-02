# Architecture

TetRay Game is split into a small gameplay core and adapter layers around it.

```text
src/app
  |
  +-- src/input      Raylib keyboard input -> GameAction
  +-- src/rendering  Raylib drawing and UI
  +-- src/audio      Raylib music and sound effects
  +-- src/assets     Runtime asset path lookup
  |
  `-- src/core       Raylib-free gameplay rules and state
```

## Layers

- `src/core` contains `Game`, `Grid`, `Block`, `TetrominoType`, `GameStatus`, `RandomBag`, and `ScoreSystem`.
- `src/rendering` draws the board, current block, next preview, score panels, controls, and overlays.
- `src/audio` owns music and sound resources.
- `src/input` converts Raylib key events into a small action enum.
- `src/assets` resolves `assets/` from installed, build, and development layouts.
- `src/app` creates the window, updates audio, applies input, advances the game clock, and calls the renderer.

## Dependency Direction

The core has no dependency on Raylib. Rendering, input, and audio depend on Raylib and on the core's public model. This keeps gameplay logic testable without opening a window and keeps CI headless.

## Boundary Check

Run:

```bash
bash scripts/check-core-boundary.sh
```

The script fails if Raylib rendering, audio, font, or input APIs appear in `src/core`.
