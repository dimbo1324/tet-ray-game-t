#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "core/LevelSystem.h"
#include "core/constants.h"

TEST_CASE("LevelSystem maps cleared lines to Tetris levels")
{
    CHECK(tetris::LevelSystem::levelForLines(-1) == 1);
    CHECK(tetris::LevelSystem::levelForLines(0) == 1);
    CHECK(tetris::LevelSystem::levelForLines(9) == 1);
    CHECK(tetris::LevelSystem::levelForLines(10) == 2);
    CHECK(tetris::LevelSystem::levelForLines(29) == 3);
}

TEST_CASE("LevelSystem lowers drop interval by level and clamps at minimum")
{
    CHECK(tetris::LevelSystem::dropIntervalForLevel(0) == Catch::Approx(tetris::kBaseDropIntervalSeconds));
    CHECK(tetris::LevelSystem::dropIntervalForLevel(1) == Catch::Approx(tetris::kBaseDropIntervalSeconds));
    CHECK(tetris::LevelSystem::dropIntervalForLevel(2) ==
          Catch::Approx(tetris::kBaseDropIntervalSeconds - tetris::kDropIntervalLevelStepSeconds));
    CHECK(tetris::LevelSystem::dropIntervalForLevel(100) == Catch::Approx(tetris::kMinimumDropIntervalSeconds));
}
