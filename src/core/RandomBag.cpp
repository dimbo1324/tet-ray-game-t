#include "RandomBag.h"

#include <algorithm>

namespace tetris
{
    RandomBag::RandomBag()
        : RandomBag(std::random_device{}())
    {
    }

    RandomBag::RandomBag(std::uint32_t seed)
        : engine_(seed)
    {
        refillAndShuffle();
    }

    TetrominoType RandomBag::next()
    {
        if (bag_.empty())
        {
            refillAndShuffle();
        }

        TetrominoType type = bag_.back();
        bag_.pop_back();
        return type;
    }

    void RandomBag::reset()
    {
        bag_.clear();
        refillAndShuffle();
    }

    void RandomBag::refillAndShuffle()
    {
        bag_.assign(kTetrominoTypes.begin(), kTetrominoTypes.end());
        std::shuffle(bag_.begin(), bag_.end(), engine_);
    }
}
