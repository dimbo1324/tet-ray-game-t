#ifndef TETRIS_RENDERING_UI_LAYOUT_H
#define TETRIS_RENDERING_UI_LAYOUT_H

#include "RenderingConstants.h"

#include <algorithm>

#include <raylib.h>

namespace tetris
{
    struct UiLayout
    {
        Vector2 titlePosition;
        Vector2 subtitlePosition;
        Rectangle boardFrame;
        int boardOriginX;
        int boardOriginY;
        Rectangle scorePanel;
        Rectangle scoreValue;
        Vector2 levelPosition;
        Vector2 linesPosition;
        Rectangle statusBadge;
        Rectangle nextPanel;
        Rectangle nextPreview;
        Rectangle controlsPanel;
        Vector2 controlsLine1;
        Vector2 controlsLine2;
        Vector2 controlsLine3;
        Vector2 controlsLine4;
        Vector2 controlsLine5;
        Vector2 controlsLine6;
        Rectangle overlay;
        Rectangle overlayTitle;
        Rectangle overlayScore;
        Rectangle overlayHint;
    };

    inline UiLayout makeUiLayout()
    {
        const int screenWidth = std::max(GetScreenWidth(), kWindowWidth);
        const int screenHeight = std::max(GetScreenHeight(), kWindowHeight);
        const int boardFrameWidth = kBoardPixelWidth + (kBoardPadding * 2);
        const int boardFrameHeight = kBoardPixelHeight + (kBoardPadding * 2);
        const int contentWidth = boardFrameWidth + kPanelGap + kSidePanelWidth;
        const int contentX = std::max(kWindowPadding, (screenWidth - contentWidth) / 2);
        const int boardY = std::max(70, (screenHeight - boardFrameHeight) / 2 + 20);
        const int sidePanelX = contentX + boardFrameWidth + kPanelGap;

        UiLayout layout{};
        layout.titlePosition = {static_cast<float>(contentX + 18), 12.0f};
        layout.subtitlePosition = {static_cast<float>(contentX + 25), 43.0f};
        layout.boardFrame = {static_cast<float>(contentX), static_cast<float>(boardY),
                             static_cast<float>(boardFrameWidth), static_cast<float>(boardFrameHeight)};
        layout.boardOriginX = contentX + kBoardPadding;
        layout.boardOriginY = boardY + kBoardPadding;

        layout.scorePanel = {static_cast<float>(sidePanelX), 24.0f, static_cast<float>(kSidePanelWidth), 154.0f};
        layout.scoreValue = {static_cast<float>(sidePanelX + 12), 66.0f,
                             static_cast<float>(kSidePanelWidth - 24), 36.0f};
        layout.levelPosition = {static_cast<float>(sidePanelX + 20), 118.0f};
        layout.linesPosition = {static_cast<float>(sidePanelX + 20), 142.0f};
        layout.statusBadge = {static_cast<float>(sidePanelX + kSidePanelWidth - 88), 114.0f, 68.0f, 42.0f};

        layout.nextPanel = {static_cast<float>(sidePanelX), 205.0f, static_cast<float>(kSidePanelWidth), 180.0f};
        layout.nextPreview = {static_cast<float>(sidePanelX + 28), 253.0f,
                              static_cast<float>(kSidePanelWidth - 56), 116.0f};

        layout.controlsPanel = {static_cast<float>(sidePanelX), 415.0f, static_cast<float>(kSidePanelWidth), 210.0f};
        layout.controlsLine1 = {static_cast<float>(sidePanelX + 20), 461.0f};
        layout.controlsLine2 = {static_cast<float>(sidePanelX + 20), 487.0f};
        layout.controlsLine3 = {static_cast<float>(sidePanelX + 20), 513.0f};
        layout.controlsLine4 = {static_cast<float>(sidePanelX + 20), 539.0f};
        layout.controlsLine5 = {static_cast<float>(sidePanelX + 20), 565.0f};
        layout.controlsLine6 = {static_cast<float>(sidePanelX + 20), 591.0f};

        layout.overlay = {static_cast<float>(contentX + 12), static_cast<float>(boardY + 180), 290.0f, 145.0f};
        layout.overlayTitle = {layout.overlay.x, layout.overlay.y + 24.0f, layout.overlay.width, 34.0f};
        layout.overlayScore = {layout.overlay.x, layout.overlay.y + 72.0f, layout.overlay.width, 24.0f};
        layout.overlayHint = {layout.overlay.x, layout.overlay.y + 110.0f, layout.overlay.width, 20.0f};

        return layout;
    }
}

#endif
