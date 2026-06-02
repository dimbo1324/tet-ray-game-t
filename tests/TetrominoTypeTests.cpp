#include <catch2/catch_test_macros.hpp>

#include "core/TetrominoType.h"

TEST_CASE("toCellIndex maps tetromino types to stable grid cell ids")
{
    CHECK(tetris::toCellIndex(tetris::TetrominoType::Empty) == 0U);
    CHECK(tetris::toCellIndex(tetris::TetrominoType::I) == 1U);
    CHECK(tetris::toCellIndex(tetris::TetrominoType::J) == 2U);
    CHECK(tetris::toCellIndex(tetris::TetrominoType::L) == 3U);
    CHECK(tetris::toCellIndex(tetris::TetrominoType::O) == 4U);
    CHECK(tetris::toCellIndex(tetris::TetrominoType::S) == 5U);
    CHECK(tetris::toCellIndex(tetris::TetrominoType::T) == 6U);
    CHECK(tetris::toCellIndex(tetris::TetrominoType::Z) == 7U);
}
