#ifndef TETRIS_CORE_BLOCK_H
#define TETRIS_CORE_BLOCK_H

#include "Position.h"

#include <map>
#include <vector>

namespace tetris
{
    class Block
    {
    public:
        Block();

        virtual ~Block() = default;

        void move(int rowDelta, int colDelta);

        std::vector<Position> getCellsPositions() const;

        void rotate();

        void undoRotation();

        int id = 0;
        std::map<int, std::vector<Position>> cells;

    protected:
        int rotationState;
        int rowOffset;
        int colOffset;
    };

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
