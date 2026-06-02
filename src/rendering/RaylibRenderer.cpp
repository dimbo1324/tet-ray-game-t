#include "RaylibRenderer.h"

#include "Colors.h"
#include "RenderingConstants.h"
#include "UiLayout.h"
#include "UiTheme.h"

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

namespace tetris
{
    namespace
    {
        const char *pathString(const std::filesystem::path &path)
        {
            static thread_local std::string value;
            value = path.string();
            return value.c_str();
        }

        void drawCell(int x, int y, int size, Color color)
        {
            const Rectangle outer{static_cast<float>(x), static_cast<float>(y), static_cast<float>(size),
                                  static_cast<float>(size)};
            DrawRectangleRounded(outer, kCellRadius, 6, color);
            DrawRectangleRoundedLines(outer, kCellRadius, 6, kThemeGridLine);

            const Rectangle highlight{static_cast<float>(x + 3), static_cast<float>(y + 3),
                                      static_cast<float>(size - 6), 4.0f};
            DrawRectangleRounded(highlight, 0.45f, 4, Fade(WHITE, 0.22f));
        }
    }

    RaylibRenderer::RaylibRenderer(const ResourcePaths &resourcePaths)
    {
        const auto fontPath = resourcePaths.font("Press_Start_2P/PressStart2P-Regular.ttf");
        if (!FileExists(pathString(fontPath)))
        {
            std::cerr << "Missing asset: " << fontPath << '\n';
        }

        font_ = LoadFontEx(pathString(fontPath), 64, nullptr, 0);
        if (font_.texture.id == 0)
        {
            std::cerr << "Failed to load font: " << fontPath << '\n';
        }
    }

    RaylibRenderer::~RaylibRenderer()
    {
        UnloadFont(font_);
    }

    void RaylibRenderer::draw(const Game &game) const
    {
        BeginDrawing();
        ClearBackground(kThemeBackground);

        const UiLayout layout = makeUiLayout();

        DrawTextEx(font_, "TETRAY", layout.titlePosition, 26.0f, 1.0f, kThemeText);
        DrawTextEx(font_, "C++23 / RAYLIB", layout.subtitlePosition, 11.0f, 1.0f, kThemeMutedText);

        DrawRectangleRounded(layout.boardFrame, 0.035f, 8, kThemeBoardBackground);
        DrawRectangleRoundedLines(layout.boardFrame, 0.035f, 8, kThemePanelBorder);
        drawGrid(game.grid());
        drawBlock(game.currentBlock(), layout.boardOriginX, layout.boardOriginY);

        drawSidePanel(game);
        drawNextBlock(game.nextBlock());
        drawOverlay(game);

        EndDrawing();
    }

    void RaylibRenderer::drawGrid(const Grid &grid) const
    {
        const UiLayout layout = makeUiLayout();
        for (int row = 0; row < grid.rowCount(); ++row)
        {
            for (int col = 0; col < grid.colCount(); ++col)
            {
                drawCell(col * kCellSize + layout.boardOriginX, row * kCellSize + layout.boardOriginY, kCellSize - 1,
                         colorFor(grid.cell(row, col)));
            }
        }
    }

    void RaylibRenderer::drawBlock(const Block &block, int offsetX, int offsetY) const
    {
        const auto tiles = block.cellPositions();
        for (const auto &pos : tiles)
        {
            drawCell(pos.col * kCellSize + offsetX, pos.row * kCellSize + offsetY, kCellSize - 1, colorFor(block.type()));
        }
    }

    void RaylibRenderer::drawNextBlock(const Block &block) const
    {
        if (block.isEmpty())
        {
            return;
        }

        const auto tiles = block.cellPositions();
        const auto [minRowIt, maxRowIt] = std::minmax_element(
            tiles.begin(), tiles.end(), [](const Position &left, const Position &right) { return left.row < right.row; });
        const auto [minColIt, maxColIt] = std::minmax_element(
            tiles.begin(), tiles.end(), [](const Position &left, const Position &right) { return left.col < right.col; });

        const UiLayout layout = makeUiLayout();
        const int previewWidth = (maxColIt->col - minColIt->col + 1) * kNextPreviewCellSize;
        const int previewHeight = (maxRowIt->row - minRowIt->row + 1) * kNextPreviewCellSize;
        const int startX = static_cast<int>(layout.nextPreview.x + (layout.nextPreview.width - previewWidth) / 2.0f);
        const int startY = static_cast<int>(layout.nextPreview.y + (layout.nextPreview.height - previewHeight) / 2.0f);

        for (const auto &pos : tiles)
        {
            const int x = startX + (pos.col - minColIt->col) * kNextPreviewCellSize;
            const int y = startY + (pos.row - minRowIt->row) * kNextPreviewCellSize;
            drawCell(x, y, kNextPreviewCellSize - 1, colorFor(block.type()));
        }
    }

    void RaylibRenderer::drawSidePanel(const Game &game) const
    {
        const UiLayout layout = makeUiLayout();
        drawPanel(layout.scorePanel, "SCORE");

        char scoreText[16];
        std::snprintf(scoreText, sizeof(scoreText), "%d", game.score());
        drawTextCentered(scoreText, layout.scoreValue, 28.0f, kThemeAccent);

        char levelText[24];
        std::snprintf(levelText, sizeof(levelText), "LEVEL %d", game.level());
        DrawTextEx(font_, levelText, layout.levelPosition, 14.0f, 1.0f, kThemeText);

        char linesText[24];
        std::snprintf(linesText, sizeof(linesText), "LINES %d", game.totalLinesCleared());
        DrawTextEx(font_, linesText, layout.linesPosition, 14.0f, 1.0f, kThemeText);

        DrawRectangleRounded(layout.statusBadge, 0.18f, 6, game.isPaused() ? Fade(kThemeWarning, 0.24f) : Fade(kThemeAccent, 0.16f));
        DrawRectangleRoundedLines(layout.statusBadge, 0.18f, 6, game.isPaused() ? kThemeWarning : kThemePanelBorder);
        drawTextCentered(game.isPaused() ? "PAUSED" : "LIVE", layout.statusBadge, 9.0f, game.isPaused() ? kThemeWarning : kThemeMutedText);

        drawPanel(layout.nextPanel, "NEXT");

        drawPanel(layout.controlsPanel, "CONTROLS");
        DrawTextEx(font_, "LEFT/RIGHT MOVE", layout.controlsLine1, 12.0f, 1.0f, kThemeMutedText);
        DrawTextEx(font_, "UP         ROTATE", layout.controlsLine2, 12.0f, 1.0f, kThemeMutedText);
        DrawTextEx(font_, "DOWN       SOFT DROP", layout.controlsLine3, 12.0f, 1.0f, kThemeMutedText);
        DrawTextEx(font_, "SPACE      HARD DROP", layout.controlsLine4, 12.0f, 1.0f, kThemeMutedText);
        DrawTextEx(font_, "P/ESC      PAUSE", layout.controlsLine5, 12.0f, 1.0f, kThemeMutedText);
        DrawTextEx(font_, "ENTER      RESTART", layout.controlsLine6, 12.0f, 1.0f, kThemeMutedText);
    }

    void RaylibRenderer::drawOverlay(const Game &game) const
    {
        if (!game.isPaused() && !game.isGameOver())
        {
            return;
        }

        const UiLayout layout = makeUiLayout();
        if (game.isPaused())
        {
            DrawRectangleRounded(layout.boardFrame, 0.035f, 8, Fade(kThemeWarning, 0.08f));
        }

        DrawRectangleRounded(layout.overlay, 0.08f, 10, kThemeOverlay);
        DrawRectangleRoundedLines(layout.overlay, 0.08f, 10, kThemePanelBorder);

        if (game.isGameOver())
        {
            drawTextCentered("GAME OVER", layout.overlayTitle, 22.0f, kThemeDanger);

            char finalScore[32];
            std::snprintf(finalScore, sizeof(finalScore), "SCORE %d", game.score());
            drawTextCentered(finalScore, layout.overlayScore, 14.0f, kThemeText);
            drawTextCentered("ENTER / SPACE TO RESTART", layout.overlayHint, 10.0f, kThemeMutedText);
        }
        else
        {
            drawTextCentered("PAUSED", layout.overlayTitle, 24.0f, kThemeWarning);
            drawTextCentered("PRESS P OR ESC TO RESUME", layout.overlayHint, 10.0f, kThemeMutedText);
        }
    }

    void RaylibRenderer::drawPanel(Rectangle bounds, const char *title) const
    {
        DrawRectangleRounded(bounds, kPanelRadius, kPanelSegments, kThemePanel);
        DrawRectangleRoundedLines(bounds, kPanelRadius, kPanelSegments, kThemePanelBorder);
        DrawTextEx(font_, title, {bounds.x + 18.0f, bounds.y + 18.0f}, 15.0f, 1.0f, kThemeText);
    }

    void RaylibRenderer::drawTextCentered(const char *text, Rectangle bounds, float fontSize, Color color) const
    {
        const Vector2 size = MeasureTextEx(font_, text, fontSize, 1.0f);
        const Vector2 position{bounds.x + (bounds.width - size.x) / 2.0f, bounds.y + (bounds.height - size.y) / 2.0f};
        DrawTextEx(font_, text, position, fontSize, 1.0f, color);
    }
}
