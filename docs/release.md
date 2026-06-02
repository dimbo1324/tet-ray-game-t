# Release Packaging

The release package is created through CMake install rules.

## Direct CMake Flow

```bash
cmake --preset release
cmake --build --preset release
cmake --install build/release --prefix dist
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
`-- README.md
```

If a root `LICENSE` file is added later, CMake will install it into `dist/`.

## Notes

The release layout keeps assets next to the executable so runtime lookup works from the package directory.
