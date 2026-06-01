#ifndef TETRIS_CORE_GRID_H
#define TETRIS_CORE_GRID_H

#include <vector>

namespace tetris
{
    class Grid
    {
    public:
        Grid();

        void initialize();

        bool isCellOutside(int row, int col) const;

        bool isCellEmpty(int row, int col) const;

        void setCell(int row, int col, int value);

        int clearFullRows();

        int rowCount() const;

        int colCount() const;

        int cell(int row, int col) const;

    private:
        bool isRowFull(int row) const;

        void clearRow(int row);

        void moveRowDown(int row, int numRowsToMove);

        int numRows;
        int numCols;
        std::vector<std::vector<int>> grid;
    };
}

#endif
