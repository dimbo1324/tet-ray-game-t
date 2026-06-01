#ifndef TETRIS_CORE_RANDOM_BAG_H
#define TETRIS_CORE_RANDOM_BAG_H

#include "TetrominoType.h"

#include <random>
#include <vector>

namespace tetris
{
    class RandomBag
    {
    public:
        RandomBag();

        explicit RandomBag(std::uint32_t seed);

        TetrominoType next();

        void reset();

    private:
        void refillAndShuffle();

        std::mt19937 engine_;
        std::vector<TetrominoType> bag_;
    };
}

#endif
