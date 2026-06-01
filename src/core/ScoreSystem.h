#ifndef TETRIS_CORE_SCORE_SYSTEM_H
#define TETRIS_CORE_SCORE_SYSTEM_H

namespace tetris
{
    class ScoreSystem
    {
    public:
        static int lineClearScore(int lines, int level);

        static int softDropScore(int cells);

        static int hardDropScore(int cells);
    };
}

#endif
