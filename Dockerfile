FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive
ENV CMAKE_GENERATOR=Ninja

RUN set -eux; \
    packages="build-essential ca-certificates cmake git libasound2-dev libgl1-mesa-dev libudev-dev libx11-dev libxcursor-dev libxi-dev libxinerama-dev libxrandr-dev ninja-build pkg-config"; \
    apt-get -o Acquire::Retries=5 update; \
    for attempt in 1 2 3 4 5; do \
        apt-get -o Acquire::Retries=5 install -y --no-install-recommends $packages && break; \
        if [ "$attempt" = "5" ]; then exit 1; fi; \
        apt-get -o Acquire::Retries=5 update; \
        sleep $((attempt * 10)); \
    done; \
    rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

CMD ["bash", "-lc", "cmake -S . -B build/docker-debug -DCMAKE_BUILD_TYPE=Debug && cmake --build build/docker-debug && ctest --test-dir build/docker-debug --output-on-failure && cmake -S . -B build/docker-release -DCMAKE_BUILD_TYPE=Release && cmake --build build/docker-release && cmake --install build/docker-release --prefix dist"]
