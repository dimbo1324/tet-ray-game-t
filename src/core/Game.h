#ifndef TETRIS_CORE_GAME_H
#define TETRIS_CORE_GAME_H

#include "Block.h"
#include "Grid.h"

#include <random>
#include <vector>

namespace tetris
{
    struct MoveDownResult
    {
        bool blockLocked = false;
        int rowsCleared = 0;
        bool gameOver = false;
    };

    class Game
    {
    public:
        Game();

        bool moveBlockLeft();

        bool moveBlockRight();

        MoveDownResult moveBlockDown(bool awardSoftDropPoint = false);

        bool rotateBlock();

        void reset();

        bool isGameOver() const;

        int score() const;

        const Grid &grid() const;

        const Block &currentBlock() const;

        const Block &nextBlock() const;

    private:
        bool isBlockOutside() const;

        bool blockFits() const;

        int lockBlock();

        void updateScore(int linesCleared, int moveDownPoints);

        Block getRandomBlock();

        std::vector<Block> getAllBlocks();

        Grid grid_;
        std::vector<Block> blocks_;
        Block currentBlock_;
        Block nextBlock_;
        std::mt19937 randomEngine_;
        bool gameOver_;
        int gameScore_;
    };
}

#endif
