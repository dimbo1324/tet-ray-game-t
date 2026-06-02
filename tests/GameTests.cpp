#include <catch2/catch_test_macros.hpp>

#include "core/Game.h"
#include "core/LevelSystem.h"
#include "core/ScoreSystem.h"

TEST_CASE("Game starts in initial running state")
{
    const tetris::Game game;

    CHECK(game.status() == tetris::GameStatus::Running);
    CHECK(game.isRunning());
    CHECK(game.score() == 0);
    CHECK(game.level() == 1);
    CHECK(game.totalLinesCleared() == 0);
    CHECK(game.dropIntervalSeconds() == tetris::LevelSystem::dropIntervalForLevel(1));
}

TEST_CASE("Game toggles pause and resume")
{
    tetris::Game game;

    game.togglePause();
    CHECK(game.isPaused());

    game.togglePause();
    CHECK(game.isRunning());
}

TEST_CASE("Game ignores movement and drops while paused")
{
    tetris::Game game;
    game.togglePause();

    const auto before = game.currentBlock().cellPositions();
    const int scoreBefore = game.score();

    CHECK_FALSE(game.moveBlockLeft());
    CHECK_FALSE(game.moveBlockRight());
    CHECK_FALSE(game.rotateBlock());

    const auto softDrop = game.softDrop();
    const auto hardDrop = game.hardDrop();

    CHECK_FALSE(softDrop.blockLocked);
    CHECK(softDrop.rowsDropped == 0);
    CHECK_FALSE(hardDrop.blockLocked);
    CHECK(hardDrop.rowsDropped == 0);
    CHECK(game.score() == scoreBefore);
    CHECK(game.currentBlock().cellPositions() == before);
}

TEST_CASE("Game hard drop locks the active block and awards score")
{
    tetris::Game game;

    const auto result = game.hardDrop();

    CHECK(result.blockLocked);
    CHECK(result.rowsDropped > 0);
    CHECK(game.score() >= tetris::ScoreSystem::hardDropScore(result.rowsDropped));
    CHECK(game.isRunning());
}

TEST_CASE("Game soft drop can award score")
{
    tetris::Game game;
    const int scoreBefore = game.score();

    const auto result = game.softDrop();

    CHECK(result.rowsDropped == 1);
    CHECK(game.score() == scoreBefore + 1);
}

TEST_CASE("Game reset restores initial state")
{
    tetris::Game game;

    game.hardDrop();
    game.togglePause();
    game.reset();

    CHECK(game.isRunning());
    CHECK(game.score() == 0);
    CHECK(game.level() == 1);
    CHECK(game.totalLinesCleared() == 0);
}

TEST_CASE("Game over blocks movement and drops")
{
    tetris::Game game;

    for (int i = 0; i < 500 && !game.isGameOver(); ++i)
    {
        game.hardDrop();
    }

    REQUIRE(game.isGameOver());

    const int scoreBefore = game.score();
    CHECK_FALSE(game.moveBlockLeft());
    CHECK_FALSE(game.moveBlockRight());
    CHECK_FALSE(game.rotateBlock());

    const auto softDrop = game.softDrop();
    const auto hardDrop = game.hardDrop();

    CHECK_FALSE(softDrop.blockLocked);
    CHECK_FALSE(hardDrop.blockLocked);
    CHECK(softDrop.gameOver);
    CHECK(hardDrop.gameOver);
    CHECK(game.score() == scoreBefore);
}
