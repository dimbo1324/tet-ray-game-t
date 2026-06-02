#include <catch2/catch_test_macros.hpp>

#include "assets/ResourcePaths.h"

#include <filesystem>

TEST_CASE("ResourcePaths resolves assets next to executable without machine-specific paths")
{
    const auto root = std::filesystem::temp_directory_path() / "tet_ray_game_resource_paths_test";
    const auto assetRoot = root / "bin" / "assets";

    std::filesystem::remove_all(root);
    std::filesystem::create_directories(assetRoot / "fonts");
    std::filesystem::create_directories(assetRoot / "sounds");

    const auto executable = root / "bin" / "tet_ray_game_app";
    const tetris::ResourcePaths paths(executable.string().c_str());

    CHECK(paths.assetRoot() == std::filesystem::weakly_canonical(assetRoot));
    CHECK(paths.font("Example/Font.ttf") == paths.assetRoot() / "fonts" / "Example/Font.ttf");
    CHECK(paths.sound("rotate.mp3") == paths.assetRoot() / "sounds" / "rotate.mp3");

    std::filesystem::remove_all(root);
}
