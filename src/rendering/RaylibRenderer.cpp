#include "RaylibRenderer.h"

#include "Colors.h"
#include "RenderingConstants.h"
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

        DrawTextEx(font_, "TETRAY", {26.0f, 12.0f}, 26.0f, 1.0f, kThemeText);
        DrawTextEx(font_, "C++23 / RAYLIB", {33.0f, 43.0f}, 11.0f, 1.0f, kThemeMutedText);

        DrawRectangleRounded({8.0f, 70.0f, static_cast<float>(kBoardPixelWidth + 14),
                              static_cast<float>(kBoardPixelHeight + 14)},
                             0.035f, 8, kThemeBoardBackground);
        DrawRectangleRoundedLines({8.0f, 70.0f, static_cast<float>(kBoardPixelWidth + 14),
                                   static_cast<float>(kBoardPixelHeight + 14)},
                                  0.035f, 8, kThemePanelBorder);
        drawGrid(game.grid());
        drawBlock(game.currentBlock(), kExtraPixels, kExtraPixels);

        drawSidePanel(game);
        drawNextBlock(game.nextBlock());
        drawOverlay(game);

        EndDrawing();
    }

    void RaylibRenderer::drawGrid(const Grid &grid) const
    {
        for (int row = 0; row < grid.rowCount(); ++row)
        {
            for (int col = 0; col < grid.colCount(); ++col)
            {
                drawCell(col * kCellSize + kExtraPixels, row * kCellSize + kExtraPixels + 70, kCellSize - 1,
                         colorFor(grid.cell(row, col)));
            }
        }
    }

    void RaylibRenderer::drawBlock(const Block &block, int offsetX, int offsetY) const
    {
        const auto tiles = block.cellPositions();
        for (const auto &pos : tiles)
        {
            drawCell(pos.col * kCellSize + offsetX, pos.row * kCellSize + offsetY + 70, kCellSize - 1,
                     colorFor(block.type()));
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

        constexpr int previewCellSize = 24;
        const int previewWidth = (maxColIt->col - minColIt->col + 1) * previewCellSize;
        const int previewHeight = (maxRowIt->row - minRowIt->row + 1) * previewCellSize;
        const int startX = kSidePanelX + (kSidePanelWidth - previewWidth) / 2;
        const int startY = 258 + (118 - previewHeight) / 2;

        for (const auto &pos : tiles)
        {
            const int x = startX + (pos.col - minColIt->col) * previewCellSize;
            const int y = startY + (pos.row - minRowIt->row) * previewCellSize;
            drawCell(x, y, previewCellSize - 1, colorFor(block.type()));
        }
    }

    void RaylibRenderer::drawSidePanel(const Game &game) const
    {
        drawPanel({static_cast<float>(kSidePanelX), 24.0f, static_cast<float>(kSidePanelWidth), 146.0f}, "SCORE");

        char scoreText[16];
        std::snprintf(scoreText, sizeof(scoreText), "%d", game.score());
        drawTextCentered(scoreText, {static_cast<float>(kSidePanelX + 12), 64.0f, static_cast<float>(kSidePanelWidth - 24), 36.0f},
                         28.0f, kThemeAccent);

        char levelText[24];
        std::snprintf(levelText, sizeof(levelText), "LEVEL %d", game.level());
        DrawTextEx(font_, levelText, {static_cast<float>(kSidePanelX + 20), 116.0f}, 14.0f, 1.0f, kThemeText);

        char linesText[24];
        std::snprintf(linesText, sizeof(linesText), "LINES %d", game.totalLinesCleared());
        DrawTextEx(font_, linesText, {static_cast<float>(kSidePanelX + 20), 140.0f}, 14.0f, 1.0f, kThemeText);

        drawPanel({static_cast<float>(kSidePanelX), 205.0f, static_cast<float>(kSidePanelWidth), 175.0f}, "NEXT");

        drawPanel({static_cast<float>(kSidePanelX), 410.0f, static_cast<float>(kSidePanelWidth), 205.0f}, "CONTROLS");
        DrawTextEx(font_, "< >  MOVE", {static_cast<float>(kSidePanelX + 20), 456.0f}, 12.0f, 1.0f, kThemeMutedText);
        DrawTextEx(font_, "^    ROTATE", {static_cast<float>(kSidePanelX + 20), 482.0f}, 12.0f, 1.0f, kThemeMutedText);
        DrawTextEx(font_, "v    SOFT DROP", {static_cast<float>(kSidePanelX + 20), 508.0f}, 12.0f, 1.0f, kThemeMutedText);
        DrawTextEx(font_, "SPACE HARD DROP", {static_cast<float>(kSidePanelX + 20), 534.0f}, 12.0f, 1.0f, kThemeMutedText);
        DrawTextEx(font_, "P/ESC PAUSE", {static_cast<float>(kSidePanelX + 20), 560.0f}, 12.0f, 1.0f, kThemeMutedText);
        DrawTextEx(font_, "ENTER RESTART", {static_cast<float>(kSidePanelX + 20), 586.0f}, 12.0f, 1.0f, kThemeMutedText);
    }

    void RaylibRenderer::drawOverlay(const Game &game) const
    {
        if (!game.isPaused() && !game.isGameOver())
        {
            return;
        }

        const Rectangle overlay{20.0f, 250.0f, 290.0f, 145.0f};
        DrawRectangleRounded(overlay, 0.08f, 10, kThemeOverlay);
        DrawRectangleRoundedLines(overlay, 0.08f, 10, kThemePanelBorder);

        if (game.isGameOver())
        {
            drawTextCentered("GAME OVER", {20.0f, 274.0f, 290.0f, 34.0f}, 22.0f, kThemeDanger);

            char finalScore[32];
            std::snprintf(finalScore, sizeof(finalScore), "SCORE %d", game.score());
            drawTextCentered(finalScore, {20.0f, 322.0f, 290.0f, 24.0f}, 14.0f, kThemeText);
            drawTextCentered("ENTER / SPACE TO RESTART", {20.0f, 360.0f, 290.0f, 20.0f}, 10.0f, kThemeMutedText);
        }
        else
        {
            drawTextCentered("PAUSED", {20.0f, 286.0f, 290.0f, 34.0f}, 24.0f, kThemeWarning);
            drawTextCentered("PRESS P OR ESC TO RESUME", {20.0f, 345.0f, 290.0f, 20.0f}, 10.0f, kThemeMutedText);
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
