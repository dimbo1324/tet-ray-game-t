#ifndef TETRIS_RENDERING_RAYLIB_RENDERER_H
#define TETRIS_RENDERING_RAYLIB_RENDERER_H

#include "assets/ResourcePaths.h"
#include "core/Block.h"
#include "core/Game.h"
#include "core/Grid.h"

#include <raylib.h>

namespace tetris
{
    class RaylibRenderer
    {
    public:
        explicit RaylibRenderer(const ResourcePaths &resourcePaths);

        ~RaylibRenderer();

        RaylibRenderer(const RaylibRenderer &) = delete;
        RaylibRenderer &operator=(const RaylibRenderer &) = delete;

        void draw(const Game &game) const;

    private:
        void drawGrid(const Grid &grid) const;

        void drawBlock(const Block &block, int offsetX, int offsetY) const;

        void drawNextBlock(const Block &block) const;

        Font font_{};
    };
}

#endif
