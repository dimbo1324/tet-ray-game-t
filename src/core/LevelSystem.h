#ifndef TETRIS_CORE_LEVEL_SYSTEM_H
#define TETRIS_CORE_LEVEL_SYSTEM_H

namespace tetris
{
    class LevelSystem
    {
    public:
        static int levelForLines(int totalLinesCleared);

        static double dropIntervalForLevel(int level);
    };
}

#endif
