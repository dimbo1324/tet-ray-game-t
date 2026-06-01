#ifndef TETRIS_RENDERING_CONSTANTS_H
#define TETRIS_RENDERING_CONSTANTS_H

namespace tetris
{
    constexpr int kCellSize = 30;
    constexpr int kExtraPixels = 11;
    constexpr int kWindowWidth = 500;
    constexpr int kWindowHeight = 620;
    constexpr int kTargetFPS = 60;
    constexpr int kXUiTextPosition = kCellSize * 350 / kCellSize;
    constexpr int kYUiTextPosition = kCellSize * 15 / kCellSize;
    constexpr int kFontSizeUiText = kCellSize / 1.5;
}

#endif
