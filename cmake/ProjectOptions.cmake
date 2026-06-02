option(TET_RAY_GAME_BUILD_APP "Build the Raylib desktop application" ON)
option(TET_RAY_GAME_BUILD_TESTS "Build Tet-Ray-Game unit tests" ON)
option(TET_RAY_GAME_ENABLE_WARNINGS "Enable project compiler warnings" ON)
option(TET_RAY_GAME_WARNINGS_AS_ERRORS "Treat project warnings as errors" OFF)
option(TET_RAY_GAME_ENABLE_SANITIZERS "Enable address/undefined sanitizers where supported" OFF)
option(TET_RAY_GAME_ENABLE_CLANG_TIDY "Enable clang-tidy for project targets" OFF)

function(tet_ray_game_apply_warnings target_name)
    if(NOT TET_RAY_GAME_ENABLE_WARNINGS)
        return()
    endif()

    if(MSVC)
        target_compile_options(${target_name}
            PRIVATE
                /W4
                /permissive-
        )
        if(TET_RAY_GAME_WARNINGS_AS_ERRORS)
            target_compile_options(${target_name} PRIVATE /WX)
        endif()
    else()
        target_compile_options(${target_name}
            PRIVATE
                -Wall
                -Wextra
                -Wpedantic
                -Wshadow
        )
        if(TET_RAY_GAME_WARNINGS_AS_ERRORS)
            target_compile_options(${target_name} PRIVATE -Werror)
        endif()
    endif()
endfunction()

function(tet_ray_game_apply_sanitizers target_name)
    if(NOT TET_RAY_GAME_ENABLE_SANITIZERS)
        return()
    endif()

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU" AND NOT MSVC)
        target_compile_options(${target_name}
            PRIVATE
                -fsanitize=address,undefined
                -fno-omit-frame-pointer
        )
        target_link_options(${target_name}
            PRIVATE
                -fsanitize=address,undefined
        )
    else()
        message(WARNING "Sanitizers are only enabled for GCC/Clang non-MSVC builds.")
    endif()
endfunction()

function(tet_ray_game_apply_clang_tidy target_name)
    if(NOT TET_RAY_GAME_ENABLE_CLANG_TIDY)
        return()
    endif()

    find_program(CLANG_TIDY_EXE NAMES clang-tidy)
    if(CLANG_TIDY_EXE)
        set_target_properties(${target_name}
            PROPERTIES
                CXX_CLANG_TIDY "${CLANG_TIDY_EXE};--config-file=${PROJECT_SOURCE_DIR}/.clang-tidy"
        )
    else()
        message(WARNING "TET_RAY_GAME_ENABLE_CLANG_TIDY is ON, but clang-tidy was not found.")
    endif()
endfunction()

function(tet_ray_game_apply_quality target_name)
    tet_ray_game_apply_warnings(${target_name})
    tet_ray_game_apply_sanitizers(${target_name})
    tet_ray_game_apply_clang_tidy(${target_name})
endfunction()
