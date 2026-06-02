cmake_minimum_required(VERSION 3.28)

project(TetRayGame
    VERSION 0.1.0
    DESCRIPTION "Modern C++23 Raylib Tetris game"
    LANGUAGES CXX
)

include(FetchContent)
include(CTest)

option(TET_RAY_GAME_BUILD_TESTS "Build Tet-Ray-Game unit tests" ON)

set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 6.0
    GIT_SHALLOW TRUE
    EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable(raylib)

if(TET_RAY_GAME_BUILD_TESTS AND BUILD_TESTING)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.7.1
        GIT_SHALLOW TRUE
    )

    FetchContent_MakeAvailable(Catch2)
endif()

add_library(tet_ray_game_core STATIC)

target_sources(tet_ray_game_core
    PRIVATE
        src/core/Block.cpp
        src/core/Game.cpp
        src/core/Grid.cpp
        src/core/Position.cpp
        src/core/RandomBag.cpp
        src/core/ScoreSystem.cpp
)

target_compile_features(tet_ray_game_core PUBLIC cxx_std_23)

set_target_properties(tet_ray_game_core
    PROPERTIES
        CXX_EXTENSIONS OFF
        CXX_SCAN_FOR_MODULES OFF
)

target_include_directories(tet_ray_game_core
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
)

add_executable(tet_ray_game_app)

target_sources(tet_ray_game_app
    PRIVATE
        src/app/main.cpp
        src/assets/ResourcePaths.cpp
        src/audio/AudioService.cpp
        src/input/InputController.cpp
        src/rendering/Colors.cpp
        src/rendering/RaylibRenderer.cpp
)

target_compile_features(tet_ray_game_app PRIVATE cxx_std_23)

set_target_properties(tet_ray_game_app
    PROPERTIES
        CXX_EXTENSIONS OFF
        CXX_SCAN_FOR_MODULES OFF
)

target_include_directories(tet_ray_game_app
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(tet_ray_game_app
    PRIVATE
        tet_ray_game_core
        raylib
)

add_custom_command(TARGET tet_ray_game_app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:tet_ray_game_app>/assets
    COMMENT "Copying game assets"
    VERBATIM
)

if(TET_RAY_GAME_BUILD_TESTS AND BUILD_TESTING)
    add_executable(tet_ray_game_tests)

    target_sources(tet_ray_game_tests
        PRIVATE
            tests/BlockTests.cpp
            tests/GameTests.cpp
            tests/GridTests.cpp
            tests/RandomBagTests.cpp
            tests/ScoreSystemTests.cpp
    )

    target_compile_features(tet_ray_game_tests PRIVATE cxx_std_23)

    set_target_properties(tet_ray_game_tests
        PROPERTIES
            CXX_EXTENSIONS OFF
            CXX_SCAN_FOR_MODULES OFF
    )

    target_link_libraries(tet_ray_game_tests
        PRIVATE
            tet_ray_game_core
            Catch2::Catch2WithMain
    )

    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
    include(Catch)
    catch_discover_tests(tet_ray_game_tests)
endif()

install(TARGETS tet_ray_game_app
    RUNTIME DESTINATION .
)

install(DIRECTORY assets
    DESTINATION .
)

install(FILES README.md
    DESTINATION .
)

if(EXISTS "${PROJECT_SOURCE_DIR}/LICENSE")
    install(FILES LICENSE
        DESTINATION .
    )
endif()
