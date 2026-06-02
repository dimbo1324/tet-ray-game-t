# Docker

The default Docker environment is for building, testing, and packaging. It is not a GUI runtime.

## Builder Image

```bash
docker build -t tet-ray-game-builder .
```

If the default Ubuntu mirror is unhealthy, pass a replacement mirror:

```bash
docker build --build-arg UBUNTU_MIRROR=http://archive.ubuntu.com/ubuntu -t tet-ray-game-builder .
```

## Compose Builder

```bash
docker compose run --rm builder
```

The builder uses separate container build directories:

- `build/docker-debug`
- `build/docker-release`

This avoids clashing with host CMake preset directories such as `build/debug`.

## Docker Apt Mirror Issues

The Dockerfile uses apt retry loops because Ubuntu mirrors can occasionally return `503 Service Unavailable`. If Docker still fails during package installation, retry later or pass `UBUNTU_MIRROR` with a healthier Ubuntu mirror.

## Experimental Linux X11 Runner

An optional `docker-compose.gui.yml` file is provided for Linux X11 hosts only. It is not used by CI and is not part of the default builder flow.

Example:

```bash
xhost +local:docker
docker compose -f docker-compose.gui.yml run --rm game-x11
```

This requires a Linux desktop session, X11 socket access, and a display-capable host. Wayland, macOS, and Windows setups may need a different approach.
