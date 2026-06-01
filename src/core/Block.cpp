#include "Block.h"

#include <stdexcept>
#include <utility>

namespace tetris
{
    Block::Block()
        : Block(TetrominoType::Empty)
    {
    }

    Block::Block(TetrominoType type)
        : type_(type),
          rotationState_(0),
          rowOffset_(0),
          colOffset_(0)
    {
    }

    void Block::move(int rowDelta, int colDelta)
    {
        rowOffset_ += rowDelta;
        colOffset_ += colDelta;
    }

    std::vector<Position> Block::cellPositions() const
    {
        auto it = cells_.find(rotationState_);
        if (it == cells_.end())
        {
            throw std::out_of_range("Invalid rotation state in Block::cellPositions()");
        }

        const auto &baseTiles = it->second;
        std::vector<Position> movedTiles;
        movedTiles.reserve(baseTiles.size());

        for (const auto &pos : baseTiles)
        {
            movedTiles.push_back({pos.row + rowOffset_, pos.col + colOffset_});
        }
        return movedTiles;
    }

    void Block::rotate()
    {
        if (cells_.empty())
        {
            throw std::runtime_error("Block cells are empty");
        }
        rotationState_ = (rotationState_ + 1) % static_cast<int>(cells_.size());
    }

    void Block::undoRotation()
    {
        if (cells_.empty())
        {
            throw std::runtime_error("Block cells are empty");
        }
        rotationState_ = (rotationState_ == 0) ? static_cast<int>(cells_.size() - 1) : rotationState_ - 1;
    }

    TetrominoType Block::type() const
    {
        return type_;
    }

    bool Block::isEmpty() const
    {
        return type_ == TetrominoType::Empty;
    }

    int Block::rotationState() const
    {
        return rotationState_;
    }

    int Block::rowOffset() const
    {
        return rowOffset_;
    }

    int Block::colOffset() const
    {
        return colOffset_;
    }

    void Block::setCells(std::map<int, std::vector<Position>> cells)
    {
        cells_ = std::move(cells);
    }

    Block makeBlock(TetrominoType type)
    {
        switch (type)
        {
            case TetrominoType::I:
                return I_Block();
            case TetrominoType::J:
                return J_Block();
            case TetrominoType::L:
                return L_Block();
            case TetrominoType::O:
                return O_Block();
            case TetrominoType::S:
                return S_Block();
            case TetrominoType::T:
                return T_Block();
            case TetrominoType::Z:
                return Z_Block();
            case TetrominoType::Empty:
                break;
        }
        return Block();
    }

    I_Block::I_Block() : Block(TetrominoType::I)
    {
        setCells({
            {0, {{1, 0}, {1, 1}, {1, 2}, {1, 3}}},
            {1, {{0, 2}, {1, 2}, {2, 2}, {3, 2}}},
            {2, {{2, 0}, {2, 1}, {2, 2}, {2, 3}}},
            {3, {{0, 1}, {1, 1}, {2, 1}, {3, 1}}}});
        move(0, 3);
    }

    J_Block::J_Block() : Block(TetrominoType::J)
    {
        setCells({
            {0, {{0, 0}, {1, 0}, {1, 1}, {1, 2}}},
            {1, {{0, 1}, {0, 2}, {1, 1}, {2, 1}}},
            {2, {{1, 0}, {1, 1}, {1, 2}, {2, 2}}},
            {3, {{0, 1}, {1, 1}, {2, 0}, {2, 1}}}});
        move(0, 3);
    }

    L_Block::L_Block() : Block(TetrominoType::L)
    {
        setCells({
            {0, {{0, 2}, {1, 0}, {1, 1}, {1, 2}}},
            {1, {{0, 1}, {1, 1}, {2, 1}, {2, 2}}},
            {2, {{1, 0}, {1, 1}, {1, 2}, {2, 0}}},
            {3, {{0, 0}, {0, 1}, {1, 1}, {2, 1}}}});
        move(0, 3);
    }

    O_Block::O_Block() : Block(TetrominoType::O)
    {
        setCells({{0, {{0, 0}, {0, 1}, {1, 0}, {1, 1}}}});
        move(0, 3);
    }

    S_Block::S_Block() : Block(TetrominoType::S)
    {
        setCells({
            {0, {{0, 1}, {0, 2}, {1, 0}, {1, 1}}},
            {1, {{0, 1}, {1, 1}, {1, 2}, {2, 2}}},
            {2, {{1, 1}, {1, 2}, {2, 0}, {2, 1}}},
            {3, {{0, 0}, {1, 0}, {1, 1}, {2, 1}}}});
        move(0, 3);
    }

    T_Block::T_Block() : Block(TetrominoType::T)
    {
        setCells({
            {0, {{0, 1}, {1, 0}, {1, 1}, {1, 2}}},
            {1, {{0, 1}, {1, 1}, {1, 2}, {2, 1}}},
            {2, {{1, 0}, {1, 1}, {1, 2}, {2, 1}}},
            {3, {{0, 1}, {1, 0}, {1, 1}, {2, 1}}}});
        move(0, 3);
    }

    Z_Block::Z_Block() : Block(TetrominoType::Z)
    {
        setCells({
            {0, {{0, 0}, {0, 1}, {1, 1}, {1, 2}}},
            {1, {{0, 2}, {1, 1}, {1, 2}, {2, 1}}},
            {2, {{1, 0}, {1, 1}, {2, 1}, {2, 2}}},
            {3, {{0, 1}, {1, 0}, {1, 1}, {2, 0}}}});
        move(0, 3);
    }
}
