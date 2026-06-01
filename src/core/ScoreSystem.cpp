#include "ScoreSystem.h"

namespace tetris
{
    int ScoreSystem::lineClearScore(int lines, int level)
    {
        switch (lines)
        {
            case 1:
                return 100 * level;
            case 2:
                return 300 * level;
            case 3:
                return 500 * level;
            case 4:
                return 800 * level;
            default:
                return 0;
        }
    }

    int ScoreSystem::softDropScore(int cells)
    {
        return cells;
    }

    int ScoreSystem::hardDropScore(int cells)
    {
        return cells * 2;
    }
}
