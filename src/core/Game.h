#ifndef TETRIS_CORE_GAME_H
#define TETRIS_CORE_GAME_H

#include "Block.h"
#include "GameStatus.h"
#include "Grid.h"
#include "RandomBag.h"

namespace tetris
{
    struct DropResult
    {
        bool blockLocked = false;
        int rowsDropped = 0;
        int linesCleared = 0;
        bool gameOver = false;
    };

    class Game
    {
    public:
        Game();

        bool moveBlockLeft();

        bool moveBlockRight();

        DropResult softDrop();

        DropResult tickDown();

        DropResult hardDrop();

        bool rotateBlock();

        void togglePause();

        void reset();

        GameStatus status() const;

        bool isRunning() const;

        bool isPaused() const;

        bool isGameOver() const;

        int score() const;

        int level() const;

        int totalLinesCleared() const;

        double dropIntervalSeconds() const;

        const Grid &grid() const;

        const Block &currentBlock() const;

        const Block &nextBlock() const;

    private:
        bool isBlockOutside() const;

        bool blockFits() const;

        DropResult moveBlockDown(bool awardSoftDropPoint);

        int lockBlock();

        void applyLineClearScore(int linesCleared);

        void addDropScore(int score);

        Block nextRandomBlock();

        Grid grid_;
        RandomBag randomBag_;
        Block currentBlock_;
        Block nextBlock_;
        GameStatus status_;
        int gameScore_;
        int totalLinesCleared_;
    };
}

#endif
