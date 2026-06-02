cmake_minimum_required(VERSION 3.28)

project(TetRayGame
    VERSION 0.1.0
    DESCRIPTION "Modern C++23 Raylib Tetris game"
    LANGUAGES CXX
)

include(FetchContent)
include(CTest)
include(cmake/ProjectOptions.cmake)

set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

if(TET_RAY_GAME_BUILD_APP)
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
endif()

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
        src/core/LevelSystem.cpp
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

tet_ray_game_apply_quality(tet_ray_game_core)

add_library(tet_ray_game_assets STATIC)

target_sources(tet_ray_game_assets
    PRIVATE
        src/assets/ResourcePaths.cpp
)

target_compile_features(tet_ray_game_assets PUBLIC cxx_std_23)

set_target_properties(tet_ray_game_assets
    PROPERTIES
        CXX_EXTENSIONS OFF
        CXX_SCAN_FOR_MODULES OFF
)

target_include_directories(tet_ray_game_assets
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
)

tet_ray_game_apply_quality(tet_ray_game_assets)

if(TET_RAY_GAME_BUILD_APP)
    add_executable(tet_ray_game_app)

    target_sources(tet_ray_game_app
        PRIVATE
            src/app/main.cpp
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
            tet_ray_game_assets
            tet_ray_game_core
            raylib
    )

    tet_ray_game_apply_quality(tet_ray_game_app)

    add_custom_command(TARGET tet_ray_game_app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:tet_ray_game_app>/assets
        COMMENT "Copying game assets"
        VERBATIM
    )
endif()

if(TET_RAY_GAME_BUILD_TESTS AND BUILD_TESTING)
    add_executable(tet_ray_game_tests)

    target_sources(tet_ray_game_tests
        PRIVATE
            tests/BlockTests.cpp
            tests/GameTests.cpp
            tests/GridTests.cpp
            tests/LevelSystemTests.cpp
            tests/RandomBagTests.cpp
            tests/ResourcePathsTests.cpp
            tests/ScoreSystemTests.cpp
            tests/TetrominoTypeTests.cpp
    )

    target_compile_features(tet_ray_game_tests PRIVATE cxx_std_23)

    set_target_properties(tet_ray_game_tests
        PROPERTIES
            CXX_EXTENSIONS OFF
            CXX_SCAN_FOR_MODULES OFF
    )

    target_link_libraries(tet_ray_game_tests
        PRIVATE
            tet_ray_game_assets
            tet_ray_game_core
            Catch2::Catch2WithMain
    )

    tet_ray_game_apply_quality(tet_ray_game_tests)

    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
    include(Catch)
    catch_discover_tests(tet_ray_game_tests)
endif()

if(TET_RAY_GAME_BUILD_APP)
    install(TARGETS tet_ray_game_app
        RUNTIME DESTINATION .
    )
endif()

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
