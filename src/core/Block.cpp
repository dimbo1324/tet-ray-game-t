#include "Block.h"

#include <stdexcept>

namespace tetris
{
    Block::Block()
        : id(0),
          rotationState(0),
          rowOffset(0),
          colOffset(0)
    {
    }

    void Block::move(int rowDelta, int colDelta)
    {
        rowOffset += rowDelta;
        colOffset += colDelta;
    }

    std::vector<Position> Block::getCellsPositions() const
    {
        auto it = cells.find(rotationState);
        if (it == cells.end())
        {
            throw std::out_of_range("Invalid rotation state in Block::getCellsPositions()");
        }

        const auto &baseTiles = it->second;
        std::vector<Position> movedTiles;
        movedTiles.reserve(baseTiles.size());

        for (const auto &pos : baseTiles)
        {
            movedTiles.emplace_back(pos.row + rowOffset, pos.col + colOffset);
        }
        return movedTiles;
    }

    void Block::rotate()
    {
        if (cells.empty())
        {
            throw std::runtime_error("Block cells are empty");
        }
        rotationState = (rotationState + 1) % cells.size();
    }

    void Block::undoRotation()
    {
        if (cells.empty())
        {
            throw std::runtime_error("Block cells are empty");
        }
        rotationState = (rotationState == 0) ? static_cast<int>(cells.size() - 1) : rotationState - 1;
    }

    I_Block::I_Block() : Block()
    {
        id = 3;
        cells = {
            {0, {Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3)}},
            {1, {Position(0, 2), Position(1, 2), Position(2, 2), Position(3, 2)}},
            {2, {Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3)}},
            {3, {Position(0, 1), Position(1, 1), Position(2, 1), Position(3, 1)}}};
        move(0, 3);
    }

    J_Block::J_Block() : Block()
    {
        id = 2;
        cells = {
            {0, {Position(0, 0), Position(1, 0), Position(1, 1), Position(1, 2)}},
            {1, {Position(0, 1), Position(0, 2), Position(1, 1), Position(2, 1)}},
            {2, {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 2)}},
            {3, {Position(0, 1), Position(1, 1), Position(2, 0), Position(2, 1)}}};
        move(0, 3);
    }

    L_Block::L_Block() : Block()
    {
        id = 1;
        cells = {
            {0, {Position(0, 2), Position(1, 0), Position(1, 1), Position(1, 2)}},
            {1, {Position(0, 1), Position(1, 1), Position(2, 1), Position(2, 2)}},
            {2, {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 0)}},
            {3, {Position(0, 0), Position(0, 1), Position(1, 1), Position(2, 1)}}};
        move(0, 3);
    }

    O_Block::O_Block() : Block()
    {
        id = 4;
        cells = {{0, {Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1)}}};
        move(0, 3);
    }

    S_Block::S_Block() : Block()
    {
        id = 5;
        cells = {
            {0, {Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 1)}},
            {1, {Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 2)}},
            {2, {Position(1, 1), Position(1, 2), Position(2, 0), Position(2, 1)}},
            {3, {Position(0, 0), Position(1, 0), Position(1, 1), Position(2, 1)}}};
        move(0, 3);
    }

    T_Block::T_Block() : Block()
    {
        id = 6;
        cells = {
            {0, {Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2)}},
            {1, {Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 1)}},
            {2, {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 1)}},
            {3, {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 1)}}};
        move(0, 3);
    }

    Z_Block::Z_Block() : Block()
    {
        id = 7;
        cells = {
            {0, {Position(0, 0), Position(0, 1), Position(1, 1), Position(1, 2)}},
            {1, {Position(0, 2), Position(1, 1), Position(1, 2), Position(2, 1)}},
            {2, {Position(1, 0), Position(1, 1), Position(2, 1), Position(2, 2)}},
            {3, {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 0)}}};
        move(0, 3);
    }
}
