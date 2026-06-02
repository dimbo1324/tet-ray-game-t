#include "Colors.h"

namespace tetris
{
    const Color kDarkGrey = {30, 36, 52, 255};
    const Color kGreen = {83, 216, 106, 255};
    const Color kRed = {239, 86, 89, 255};
    const Color kOrange = {242, 149, 72, 255};
    const Color kYellow = {246, 216, 91, 255};
    const Color kPurple = {178, 112, 241, 255};
    const Color kCyan = {80, 206, 219, 255};
    const Color kBlue = {93, 139, 255, 255};
    const Color kLightBlue = {59, 85, 162, 255};
    const Color kDarkBlue = {44, 44, 127, 255};

    std::vector<Color> GetCellColors()
    {
        return {kDarkGrey, kGreen, kRed, kOrange, kYellow, kPurple, kCyan, kBlue};
    }

    Color colorFor(TetrominoType type)
    {
        const auto colors = GetCellColors();
        return colors.at(toCellIndex(type));
    }
}
