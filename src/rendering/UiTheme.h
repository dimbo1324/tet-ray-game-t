#ifndef TETRIS_RENDERING_UI_THEME_H
#define TETRIS_RENDERING_UI_THEME_H

#include <raylib.h>

namespace tetris
{
    constexpr Color kThemeBackground = {16, 20, 32, 255};
    constexpr Color kThemeBoardBackground = {24, 29, 43, 255};
    constexpr Color kThemePanel = {31, 40, 61, 235};
    constexpr Color kThemePanelBorder = {82, 104, 150, 255};
    constexpr Color kThemeText = {239, 244, 255, 255};
    constexpr Color kThemeMutedText = {164, 178, 207, 255};
    constexpr Color kThemeAccent = {95, 211, 255, 255};
    constexpr Color kThemeWarning = {255, 207, 89, 255};
    constexpr Color kThemeDanger = {255, 101, 101, 255};
    constexpr Color kThemeOverlay = {6, 9, 18, 185};
    constexpr Color kThemeGridLine = {42, 50, 70, 255};

    constexpr float kPanelRadius = 0.08f;
    constexpr int kPanelSegments = 8;
    constexpr float kCellRadius = 0.16f;
}

#endif
