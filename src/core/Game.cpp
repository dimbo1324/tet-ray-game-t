#include "Game.h"

#include <algorithm>

namespace tetris
{
    Game::Game()
        : grid_(),
          randomEngine_(std::random_device{}()),
          gameOver_(false),
          gameScore_(0)
    {
        blocks_ = getAllBlocks();
        currentBlock_ = getRandomBlock();
        nextBlock_ = getRandomBlock();
    }

    Block Game::getRandomBlock()
    {
        if (blocks_.empty())
        {
            blocks_ = getAllBlocks();
        }
        std::uniform_int_distribution<> dist(0, static_cast<int>(blocks_.size()) - 1);
        int randomIndex = dist(randomEngine_);
        Block block = blocks_[randomIndex];
        blocks_.erase(blocks_.begin() + randomIndex);
        return block;
    }

    std::vector<Block> Game::getAllBlocks()
    {
        return {I_Block(), J_Block(), L_Block(), O_Block(), S_Block(), T_Block(), Z_Block()};
    }

    bool Game::moveBlockLeft()
    {
        if (gameOver_)
        {
            return false;
        }

        currentBlock_.move(0, -1);
        if (isBlockOutside() || !blockFits())
        {
            currentBlock_.move(0, 1);
            return false;
        }
        return true;
    }

    bool Game::moveBlockRight()
    {
        if (gameOver_)
        {
            return false;
        }

        currentBlock_.move(0, 1);
        if (isBlockOutside() || !blockFits())
        {
            currentBlock_.move(0, -1);
            return false;
        }
        return true;
    }

    MoveDownResult Game::moveBlockDown(bool awardSoftDropPoint)
    {
        MoveDownResult result;
        if (gameOver_)
        {
            result.gameOver = true;
            return result;
        }

        currentBlock_.move(1, 0);
        if (isBlockOutside() || !blockFits())
        {
            currentBlock_.move(-1, 0);
            result.blockLocked = true;
            result.rowsCleared = lockBlock();
            result.gameOver = gameOver_;
        }

        if (awardSoftDropPoint)
        {
            updateScore(0, 1);
        }

        return result;
    }

    bool Game::rotateBlock()
    {
        if (gameOver_)
        {
            return false;
        }

        currentBlock_.rotate();
        if (isBlockOutside() || !blockFits())
        {
            currentBlock_.undoRotation();
            return false;
        }
        return true;
    }

    bool Game::isBlockOutside() const
    {
        const auto tiles = currentBlock_.getCellsPositions();
        return std::any_of(tiles.begin(), tiles.end(),
                           [this](const Position &pos) { return grid_.isCellOutside(pos.row, pos.col); });
    }

    int Game::lockBlock()
    {
        const auto tiles = currentBlock_.getCellsPositions();
        for (const auto &pos : tiles)
        {
            grid_.setCell(pos.row, pos.col, currentBlock_.id);
        }

        currentBlock_ = nextBlock_;
        if (!blockFits())
        {
            gameOver_ = true;
        }

        nextBlock_ = getRandomBlock();
        int rowsCleared = grid_.clearFullRows();
        if (rowsCleared > 0)
        {
            updateScore(rowsCleared, 0);
        }
        return rowsCleared;
    }

    bool Game::blockFits() const
    {
        const auto tiles = currentBlock_.getCellsPositions();
        return std::all_of(tiles.begin(), tiles.end(),
                           [this](const Position &pos) { return grid_.isCellEmpty(pos.row, pos.col); });
    }

    void Game::reset()
    {
        grid_.initialize();
        blocks_ = getAllBlocks();
        currentBlock_ = getRandomBlock();
        nextBlock_ = getRandomBlock();
        gameScore_ = 0;
        gameOver_ = false;
    }

    bool Game::isGameOver() const
    {
        return gameOver_;
    }

    int Game::score() const
    {
        return gameScore_;
    }

    const Grid &Game::grid() const
    {
        return grid_;
    }

    const Block &Game::currentBlock() const
    {
        return currentBlock_;
    }

    const Block &Game::nextBlock() const
    {
        return nextBlock_;
    }

    void Game::updateScore(int linesCleared, int moveDownPoints)
    {
        switch (linesCleared)
        {
            case 1:
                gameScore_ += 100;
                break;
            case 2:
                gameScore_ += 300;
                break;
            case 3:
                gameScore_ += 500;
                break;
            default:
                break;
        }
        gameScore_ += moveDownPoints;
    }
}
