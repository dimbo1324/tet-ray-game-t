#ifndef TETRIS_RENDERING_COLORS_H
#define TETRIS_RENDERING_COLORS_H

#include "core/TetrominoType.h"

#include <raylib.h>
#include <vector>

namespace tetris
{
    extern const Color kDarkGrey;
    extern const Color kGreen;
    extern const Color kRed;
    extern const Color kOrange;
    extern const Color kYellow;
    extern const Color kPurple;
    extern const Color kCyan;
    extern const Color kBlue;
    extern const Color kLightBlue;
    extern const Color kDarkBlue;

    std::vector<Color> GetCellColors();

    Color colorFor(TetrominoType type);
}

#endif
