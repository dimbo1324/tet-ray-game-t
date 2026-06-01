cmake_minimum_required(VERSION 3.28)

project(TetRayGame
    VERSION 0.1.0
    DESCRIPTION "Modern C++23 Raylib Tetris game"
    LANGUAGES CXX
)

include(FetchContent)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 6.0
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(raylib)

add_executable(tet_ray_game_app)

target_sources(tet_ray_game_app
    PRIVATE
        app/main.cpp
        app/blocks/Block.cpp
        app/colors/Colors.cpp
        app/game/Game.cpp
        app/grid/Grid.cpp
        app/positions/Position.cpp
)

target_compile_features(tet_ray_game_app PRIVATE cxx_std_23)

set_target_properties(tet_ray_game_app
    PROPERTIES
        CXX_EXTENSIONS OFF
        CXX_SCAN_FOR_MODULES OFF
)

target_include_directories(tet_ray_game_app
    PRIVATE
        ${PROJECT_SOURCE_DIR}/app
)

target_link_libraries(tet_ray_game_app PRIVATE raylib)

foreach(asset_dir IN ITEMS fonts sounds)
    add_custom_command(TARGET tet_ray_game_app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_SOURCE_DIR}/${asset_dir}
            $<TARGET_FILE_DIR:tet_ray_game_app>/${asset_dir}
        COMMENT "Copying ${asset_dir} assets"
        VERBATIM
    )
endforeach()
