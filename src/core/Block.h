#ifndef TETRIS_CORE_BLOCK_H
#define TETRIS_CORE_BLOCK_H

#include "Position.h"
#include "TetrominoType.h"

#include <map>
#include <vector>

namespace tetris
{
    class Block
    {
    public:
        Block();

        explicit Block(TetrominoType type);

        void move(int rowDelta, int colDelta);

        std::vector<Position> cellPositions() const;

        void rotate();

        void undoRotation();

        TetrominoType type() const;

        bool isEmpty() const;

        int rotationState() const;

        int rowOffset() const;

        int colOffset() const;

    protected:
        void setCells(std::map<int, std::vector<Position>> cells);

    private:
        TetrominoType type_;
        int rotationState_;
        int rowOffset_;
        int colOffset_;
        std::map<int, std::vector<Position>> cells_;
    };

    Block makeBlock(TetrominoType type);

    class I_Block : public Block
    {
    public:
        I_Block();
    };

    class J_Block : public Block
    {
    public:
        J_Block();
    };

    class L_Block : public Block
    {
    public:
        L_Block();
    };

    class O_Block : public Block
    {
    public:
        O_Block();
    };

    class S_Block : public Block
    {
    public:
        S_Block();
    };

    class T_Block : public Block
    {
    public:
        T_Block();
    };

    class Z_Block : public Block
    {
    public:
        Z_Block();
    };
}

#endif
