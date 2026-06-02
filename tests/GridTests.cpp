#include <catch2/catch_test_macros.hpp>

#include "core/Grid.h"

namespace
{
    void fillRow(tetris::Grid &grid, int row, tetris::TetrominoType type = tetris::TetrominoType::I)
    {
        for (int col = 0; col < grid.colCount(); ++col)
        {
            grid.setCell(row, col, type);
        }
    }
}

TEST_CASE("Grid starts empty")
{
    const tetris::Grid grid;

    for (int row = 0; row < grid.rowCount(); ++row)
    {
        for (int col = 0; col < grid.colCount(); ++col)
        {
            CHECK(grid.cell(row, col) == tetris::TetrominoType::Empty);
            CHECK(grid.isCellEmpty(row, col));
        }
    }
}

TEST_CASE("Grid detects outside cells")
{
    const tetris::Grid grid;

    CHECK(grid.isCellOutside(-1, 0));
    CHECK(grid.isCellOutside(0, -1));
    CHECK(grid.isCellOutside(grid.rowCount(), 0));
    CHECK(grid.isCellOutside(0, grid.colCount()));
    CHECK_FALSE(grid.isCellOutside(0, 0));
}

TEST_CASE("Grid set and get cells")
{
    tetris::Grid grid;

    grid.setCell(3, 4, tetris::TetrominoType::T);

    CHECK(grid.cell(3, 4) == tetris::TetrominoType::T);
    CHECK_FALSE(grid.isCellEmpty(3, 4));
}

TEST_CASE("Grid clears one full row")
{
    tetris::Grid grid;
    const int bottom = grid.rowCount() - 1;
    fillRow(grid, bottom);

    CHECK(grid.clearFullRows() == 1);

    for (int col = 0; col < grid.colCount(); ++col)
    {
        CHECK(grid.cell(bottom, col) == tetris::TetrominoType::Empty);
    }
}

TEST_CASE("Grid clears multiple full rows")
{
    tetris::Grid grid;
    const int bottom = grid.rowCount() - 1;
    fillRow(grid, bottom);
    fillRow(grid, bottom - 1, tetris::TetrominoType::J);

    CHECK(grid.clearFullRows() == 2);
    CHECK(grid.isCellEmpty(bottom, 0));
    CHECK(grid.isCellEmpty(bottom - 1, 0));
}

TEST_CASE("Grid moves rows above cleared rows down")
{
    tetris::Grid grid;
    const int bottom = grid.rowCount() - 1;
    fillRow(grid, bottom);
    grid.setCell(bottom - 1, 2, tetris::TetrominoType::L);

    CHECK(grid.clearFullRows() == 1);

    CHECK(grid.cell(bottom, 2) == tetris::TetrominoType::L);
    CHECK(grid.cell(bottom - 1, 2) == tetris::TetrominoType::Empty);
}

TEST_CASE("Grid preserves non-full rows")
{
    tetris::Grid grid;
    const int bottom = grid.rowCount() - 1;
    grid.setCell(bottom, 0, tetris::TetrominoType::S);
    grid.setCell(bottom, 2, tetris::TetrominoType::Z);

    CHECK(grid.clearFullRows() == 0);
    CHECK(grid.cell(bottom, 0) == tetris::TetrominoType::S);
    CHECK(grid.cell(bottom, 2) == tetris::TetrominoType::Z);
}
