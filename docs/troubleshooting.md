# Troubleshooting

## CMake Configure Fails

Check that CMake 3.28 or newer is installed and that your compiler supports C++23.

## FetchContent Download Fails

Raylib and Catch2 are downloaded during configure. Confirm network access and retry. Corporate proxies may require Git or CMake proxy configuration.

## Linux Raylib Dependencies

Install X11/OpenGL/audio development packages. Ubuntu CI and Docker use:

```text
build-essential cmake ninja-build git pkg-config ca-certificates
libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev
libgl1-mesa-dev libasound2-dev libudev-dev
```

## Docker Apt Mirror Errors

If Docker fails with `503 Service Unavailable` from Ubuntu mirrors, retry later or switch mirrors. The Dockerfile includes retry loops, but mirror outages can still last long enough to fail a build.

## Assets Do Not Load

Confirm the executable has an `assets/` directory beside it. CMake copies assets after build and CMake install includes assets in `dist/`.

## Tests Do Not Appear

Configure with tests enabled:

```bash
cmake --preset debug -DTET_RAY_GAME_BUILD_TESTS=ON
```

Then build before running CTest.

## clang-tidy Not Found

`TET_RAY_GAME_ENABLE_CLANG_TIDY=ON` warns if `clang-tidy` is missing. Install clang-tidy or turn the option off.

## Sanitizers

Sanitizers are intended for GCC/Clang non-MSVC builds. They are not enabled by default and may not be available on every local toolchain.
