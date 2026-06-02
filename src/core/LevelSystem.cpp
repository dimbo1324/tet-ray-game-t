#include "LevelSystem.h"

#include "constants.h"

#include <algorithm>

namespace tetris
{
    int LevelSystem::levelForLines(int totalLinesCleared)
    {
        return (std::max(0, totalLinesCleared) / 10) + 1;
    }

    double LevelSystem::dropIntervalForLevel(int level)
    {
        const int normalizedLevel = std::max(1, level);
        const double interval = kBaseDropIntervalSeconds - ((normalizedLevel - 1) * kDropIntervalLevelStepSeconds);
        return std::max(kMinimumDropIntervalSeconds, interval);
    }
}
