#include <catch2/catch_test_macros.hpp>

#include "core/RandomBag.h"

#include <algorithm>
#include <vector>

namespace
{
    std::vector<tetris::TetrominoType> drawTypes(tetris::RandomBag &bag, int count)
    {
        std::vector<tetris::TetrominoType> types;
        types.reserve(static_cast<std::size_t>(count));
        for (int i = 0; i < count; ++i)
        {
            types.push_back(bag.next());
        }
        return types;
    }

    void requireCompleteBag(std::vector<tetris::TetrominoType> types)
    {
        std::ranges::sort(types);
        std::vector<tetris::TetrominoType> expected(tetris::kTetrominoTypes.begin(), tetris::kTetrominoTypes.end());
        std::ranges::sort(expected);
        REQUIRE(types == expected);
    }
}

TEST_CASE("RandomBag returns each tetromino exactly once per bag")
{
    tetris::RandomBag bag(1234);

    requireCompleteBag(drawTypes(bag, 7));
    requireCompleteBag(drawTypes(bag, 7));
}

TEST_CASE("RandomBag seed produces deterministic sequences")
{
    tetris::RandomBag first(42);
    tetris::RandomBag second(42);

    REQUIRE(drawTypes(first, 28) == drawTypes(second, 28));
}
