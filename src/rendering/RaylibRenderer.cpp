#include "RaylibRenderer.h"

#include "Colors.h"
#include "RenderingConstants.h"

#include <cstdio>
#include <iostream>

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
        ClearBackground(kDarkBlue);

        DrawTextEx(font_, "Score",
                   {static_cast<float>(kXUiTextPosition), static_cast<float>(kYUiTextPosition)}, kFontSizeUiText, 0,
                   WHITE);
        DrawTextEx(font_, "Next",
                   {static_cast<float>(kXUiTextPosition + 5), static_cast<float>(kYUiTextPosition + 160)},
                   kFontSizeUiText, 0, WHITE);

        if (game.isGameOver())
        {
            DrawTextEx(font_, "GAME OVER",
                       {static_cast<float>(kXUiTextPosition - 25), static_cast<float>(kYUiTextPosition + 435)},
                       kFontSizeUiText - 2, 0, WHITE);
        }

        DrawRectangleRounded({320, 55, 170, 60}, 0.3f, 6, kLightBlue);

        char scoreText[10];
        std::snprintf(scoreText, sizeof(scoreText), "%d", game.score());
        Vector2 scoreTextSize = MeasureTextEx(font_, scoreText, 38, 2);
        DrawTextEx(font_, scoreText, {kXUiTextPosition + (140 - scoreTextSize.x) / 2, 70}, kFontSizeUiText, 0, WHITE);

        DrawRectangleRounded({320, 215, 170, 180}, 0.3f, 6, kLightBlue);

        drawGrid(game.grid());
        drawBlock(game.currentBlock(), kExtraPixels, kExtraPixels);
        drawNextBlock(game.nextBlock());

        EndDrawing();
    }

    void RaylibRenderer::drawGrid(const Grid &grid) const
    {
        const auto colors = GetCellColors();
        for (int row = 0; row < grid.rowCount(); ++row)
        {
            for (int col = 0; col < grid.colCount(); ++col)
            {
                int cellValue = grid.cell(row, col);
                DrawRectangle(col * kCellSize + kExtraPixels, row * kCellSize + kExtraPixels, kCellSize - 1,
                              kCellSize - 1, colors[cellValue]);
            }
        }
    }

    void RaylibRenderer::drawBlock(const Block &block, int offsetX, int offsetY) const
    {
        const auto colors = GetCellColors();
        const auto tiles = block.getCellsPositions();
        for (const auto &pos : tiles)
        {
            DrawRectangle(pos.col * kCellSize + offsetX, pos.row * kCellSize + offsetY, kCellSize - 1, kCellSize - 1,
                          colors.at(block.id));
        }
    }

    void RaylibRenderer::drawNextBlock(const Block &block) const
    {
        switch (block.id)
        {
            case 3:
                drawBlock(block, 255, 290);
                break;
            case 4:
                drawBlock(block, 255, 280);
                break;
            default:
                drawBlock(block, 270, 270);
                break;
        }
    }
}
