#include <catch2/catch_test_macros.hpp>

#include "core/ScoreSystem.h"

TEST_CASE("ScoreSystem scores line clears by level")
{
    CHECK(tetris::ScoreSystem::lineClearScore(0, 1) == 0);
    CHECK(tetris::ScoreSystem::lineClearScore(1, 1) == 100);
    CHECK(tetris::ScoreSystem::lineClearScore(2, 1) == 300);
    CHECK(tetris::ScoreSystem::lineClearScore(3, 1) == 500);
    CHECK(tetris::ScoreSystem::lineClearScore(4, 1) == 800);
    CHECK(tetris::ScoreSystem::lineClearScore(4, 2) == 1600);
}

TEST_CASE("ScoreSystem scores soft drops per cell")
{
    CHECK(tetris::ScoreSystem::softDropScore(0) == 0);
    CHECK(tetris::ScoreSystem::softDropScore(1) == 1);
    CHECK(tetris::ScoreSystem::softDropScore(5) == 5);
}

TEST_CASE("ScoreSystem scores hard drops at two points per cell")
{
    CHECK(tetris::ScoreSystem::hardDropScore(0) == 0);
    CHECK(tetris::ScoreSystem::hardDropScore(1) == 2);
    CHECK(tetris::ScoreSystem::hardDropScore(5) == 10);
}
