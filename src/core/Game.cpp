#include "Game.h"

#include "ScoreSystem.h"
#include "constants.h"

#include <algorithm>

namespace tetris
{
    Game::Game()
        : grid_(),
          randomBag_(),
          currentBlock_(nextRandomBlock()),
          nextBlock_(nextRandomBlock()),
          status_(GameStatus::Running),
          gameScore_(0),
          totalLinesCleared_(0)
    {
    }

    bool Game::moveBlockLeft()
    {
        if (!isRunning())
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
        if (!isRunning())
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

    DropResult Game::softDrop()
    {
        return moveBlockDown(true);
    }

    DropResult Game::tickDown()
    {
        return moveBlockDown(false);
    }

    DropResult Game::hardDrop()
    {
        DropResult result;
        if (!isRunning())
        {
            result.gameOver = isGameOver();
            return result;
        }

        while (true)
        {
            currentBlock_.move(1, 0);
            if (isBlockOutside() || !blockFits())
            {
                currentBlock_.move(-1, 0);
                break;
            }
            ++result.rowsDropped;
        }

        addDropScore(ScoreSystem::hardDropScore(result.rowsDropped));
        result.blockLocked = true;
        result.linesCleared = lockBlock();
        result.gameOver = isGameOver();
        return result;
    }

    DropResult Game::moveBlockDown(bool awardSoftDropPoint)
    {
        DropResult result;
        if (!isRunning())
        {
            result.gameOver = isGameOver();
            return result;
        }

        currentBlock_.move(1, 0);
        if (isBlockOutside() || !blockFits())
        {
            currentBlock_.move(-1, 0);
            result.blockLocked = true;
            result.linesCleared = lockBlock();
            result.gameOver = isGameOver();
            return result;
        }

        result.rowsDropped = 1;
        if (awardSoftDropPoint)
        {
            addDropScore(ScoreSystem::softDropScore(1));
        }
        return result;
    }

    bool Game::rotateBlock()
    {
        if (!isRunning())
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

    void Game::togglePause()
    {
        if (status_ == GameStatus::Running)
        {
            status_ = GameStatus::Paused;
        }
        else if (status_ == GameStatus::Paused)
        {
            status_ = GameStatus::Running;
        }
    }

    bool Game::isBlockOutside() const
    {
        const auto tiles = currentBlock_.cellPositions();
        return std::any_of(tiles.begin(), tiles.end(),
                           [this](const Position &pos) { return grid_.isCellOutside(pos.row, pos.col); });
    }

    int Game::lockBlock()
    {
        const auto tiles = currentBlock_.cellPositions();
        for (const auto &pos : tiles)
        {
            grid_.setCell(pos.row, pos.col, currentBlock_.type());
        }

        int linesCleared = grid_.clearFullRows();
        if (linesCleared > 0)
        {
            totalLinesCleared_ += linesCleared;
            applyLineClearScore(linesCleared);
        }

        currentBlock_ = nextBlock_;
        if (!blockFits())
        {
            status_ = GameStatus::GameOver;
        }

        nextBlock_ = nextRandomBlock();
        return linesCleared;
    }

    bool Game::blockFits() const
    {
        const auto tiles = currentBlock_.cellPositions();
        return std::all_of(tiles.begin(), tiles.end(),
                           [this](const Position &pos) { return grid_.isCellEmpty(pos.row, pos.col); });
    }

    void Game::reset()
    {
        grid_.initialize();
        randomBag_.reset();
        currentBlock_ = nextRandomBlock();
        nextBlock_ = nextRandomBlock();
        gameScore_ = 0;
        totalLinesCleared_ = 0;
        status_ = GameStatus::Running;
    }

    GameStatus Game::status() const
    {
        return status_;
    }

    bool Game::isRunning() const
    {
        return status_ == GameStatus::Running;
    }

    bool Game::isPaused() const
    {
        return status_ == GameStatus::Paused;
    }

    bool Game::isGameOver() const
    {
        return status_ == GameStatus::GameOver;
    }

    int Game::score() const
    {
        return gameScore_;
    }

    int Game::level() const
    {
        return (totalLinesCleared_ / 10) + 1;
    }

    int Game::totalLinesCleared() const
    {
        return totalLinesCleared_;
    }

    double Game::dropIntervalSeconds() const
    {
        const double interval = kBaseDropIntervalSeconds - ((level() - 1) * kDropIntervalLevelStepSeconds);
        return std::max(kMinimumDropIntervalSeconds, interval);
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

    void Game::applyLineClearScore(int linesCleared)
    {
        gameScore_ += ScoreSystem::lineClearScore(linesCleared, level());
    }

    void Game::addDropScore(int score)
    {
        gameScore_ += score;
    }

    Block Game::nextRandomBlock()
    {
        return makeBlock(randomBag_.next());
    }
}
