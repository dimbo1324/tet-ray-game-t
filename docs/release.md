# Release Packaging

The release package is created through CMake install rules.

## Direct CMake Flow

```bash
cmake --preset release
cmake --build --preset release
cmake --install build/release --prefix dist
```

For package-only release builds without Catch2 test targets:

```bash
cmake --preset release-no-tests
cmake --build --preset release-no-tests
cmake --install build/release-no-tests --prefix dist
```

## Helper Scripts

Linux/macOS:

```bash
./scripts/package-release.sh
```

Windows PowerShell:

```powershell
./scripts/package-release.ps1
```

## Expected Layout

```text
dist/
|-- tet_ray_game_app(.exe)
|-- assets/
|   |-- fonts/
|   `-- sounds/
|-- LICENSE
`-- README.md
```

The root `LICENSE` file is installed into `dist/`.

## Notes

The release layout keeps assets next to the executable so runtime lookup works from the package directory.
