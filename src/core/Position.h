#ifndef TETRIS_CORE_POSITION_H
#define TETRIS_CORE_POSITION_H

namespace tetris
{
    struct Position
    {
        int row{};
        int col{};

        constexpr bool operator==(const Position &other) const = default;
    };
}

#endif
