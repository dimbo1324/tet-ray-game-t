#include "Grid.h"

#include "constants.h"

#include <algorithm>

namespace tetris
{
    Grid::Grid()
        : numRows(kNumRows),
          numCols(kNumCols),
          grid(numRows, std::vector<TetrominoType>(numCols, TetrominoType::Empty))
    {
        initialize();
    }

    void Grid::initialize()
    {
        for (auto &row : grid)
        {
            std::fill(row.begin(), row.end(), TetrominoType::Empty);
        }
    }

    bool Grid::isCellOutside(int row, int col) const
    {
        return (row < 0 || row >= numRows || col < 0 || col >= numCols);
    }

    bool Grid::isCellEmpty(int row, int col) const
    {
        return !isCellOutside(row, col) && (grid[row][col] == TetrominoType::Empty);
    }

    void Grid::setCell(int row, int col, TetrominoType type)
    {
        if (!isCellOutside(row, col))
        {
            grid[row][col] = type;
        }
    }

    int Grid::clearFullRows()
    {
        int clearedRows = 0;
        for (int row = numRows - 1; row >= 0; --row)
        {
            if (isRowFull(row))
            {
                clearRow(row);
                ++clearedRows;
            }
            else if (clearedRows > 0)
            {
                moveRowDown(row, clearedRows);
            }
        }
        return clearedRows;
    }

    int Grid::rowCount() const
    {
        return numRows;
    }

    int Grid::colCount() const
    {
        return numCols;
    }

    TetrominoType Grid::cell(int row, int col) const
    {
        return grid[row][col];
    }

    bool Grid::isRowFull(int row) const
    {
        for (int col = 0; col < numCols; ++col)
        {
            if (grid[row][col] == TetrominoType::Empty)
            {
                return false;
            }
        }
        return true;
    }

    void Grid::clearRow(int row)
    {
        for (int col = 0; col < numCols; ++col)
        {
            grid[row][col] = TetrominoType::Empty;
        }
    }

    void Grid::moveRowDown(int row, int numRowsToMove)
    {
        int targetRow = row + numRowsToMove;
        if (targetRow < numRows)
        {
            grid[targetRow] = grid[row];
            clearRow(row);
        }
    }
}
