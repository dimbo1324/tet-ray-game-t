#ifndef TETRIS_RENDERING_CONSTANTS_H
#define TETRIS_RENDERING_CONSTANTS_H

namespace tetris
{
    constexpr int kCellSize = 30;
    constexpr int kExtraPixels = 11;
    constexpr int kBoardPixelWidth = 10 * kCellSize;
    constexpr int kBoardPixelHeight = 20 * kCellSize;
    constexpr int kWindowWidth = 610;
    constexpr int kWindowHeight = 700;
    constexpr int kTargetFPS = 60;
    constexpr int kSidePanelX = 340;
    constexpr int kSidePanelWidth = 250;
    constexpr int kFontSizeUiText = 20;
}

#endif
