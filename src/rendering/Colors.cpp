#include "Colors.h"

namespace tetris
    {
        const Color kDarkGrey = {26, 31, 40, 255};
        const Color kGreen = {47, 230, 23, 255};
        const Color kRed = {232, 18, 18, 255};
        const Color kOrange = {226, 116, 17, 255};
        const Color kYellow = {237, 234, 4, 255};
        const Color kPurple = {166, 0, 247, 255};
        const Color kCyan = {21, 204, 209, 255};
        const Color kBlue = {13, 64, 216, 255};
        const Color kLightBlue = {59, 85, 162, 255};
        const Color kDarkBlue = {44, 44, 127, 255};

        std::vector<Color> GetCellColors()
            {
                return {kDarkGrey, kGreen, kRed, kOrange, kYellow, kPurple, kCyan, kBlue};
            }
    }
