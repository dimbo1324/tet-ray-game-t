#include <catch2/catch_test_macros.hpp>

#include "core/Block.h"

TEST_CASE("Every tetromino type creates a non-empty block")
{
    for (auto type : tetris::kTetrominoTypes)
    {
        const auto block = tetris::makeBlock(type);

        CHECK(block.type() == type);
        CHECK_FALSE(block.isEmpty());
        CHECK_FALSE(block.cellPositions().empty());
    }
}

TEST_CASE("O block rotation leaves positions unchanged")
{
    auto block = tetris::makeBlock(tetris::TetrominoType::O);
    const auto before = block.cellPositions();

    block.rotate();

    CHECK(block.cellPositions() == before);
}

TEST_CASE("Non-O block rotation changes orientation and undo restores it")
{
    for (auto type : tetris::kTetrominoTypes)
    {
        if (type == tetris::TetrominoType::O)
        {
            continue;
        }

        auto block = tetris::makeBlock(type);
        const auto before = block.cellPositions();

        block.rotate();
        CHECK(block.cellPositions() != before);

        block.undoRotation();
        CHECK(block.cellPositions() == before);
    }
}

TEST_CASE("Block movement shifts all cell positions")
{
    auto block = tetris::makeBlock(tetris::TetrominoType::T);
    const auto before = block.cellPositions();

    block.move(2, -1);
    const auto after = block.cellPositions();

    REQUIRE(after.size() == before.size());
    for (std::size_t i = 0; i < before.size(); ++i)
    {
        CHECK(after[i].row == before[i].row + 2);
        CHECK(after[i].col == before[i].col - 1);
    }
}
