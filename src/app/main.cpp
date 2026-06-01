#include "assets/ResourcePaths.h"
#include "audio/AudioService.h"
#include "core/Game.h"
#include "input/InputController.h"
#include "rendering/RaylibRenderer.h"
#include "rendering/RenderingConstants.h"

#include <raylib.h>

using namespace tetris;

namespace
{
    bool eventTriggered(double interval)
    {
        static double lastUpdateTime = 0.0;
        double currentTime = GetTime();
        if (currentTime - lastUpdateTime >= interval)
        {
            lastUpdateTime = currentTime;
            return true;
        }
        return false;
    }

    void applyAction(GameAction action, Game &game, AudioService &audio)
    {
        switch (action)
        {
            case GameAction::MoveLeft:
                game.moveBlockLeft();
                break;
            case GameAction::MoveRight:
                game.moveBlockRight();
                break;
            case GameAction::SoftDrop:
            {
                const auto result = game.softDrop();
                if (result.linesCleared > 0)
                {
                    audio.playClear();
                }
                break;
            }
            case GameAction::Rotate:
                if (game.rotateBlock())
                {
                    audio.playRotate();
                }
                break;
            case GameAction::HardDrop:
                if (game.isGameOver())
                {
                    game.reset();
                }
                else
                {
                    const auto result = game.hardDrop();
                    if (result.linesCleared > 0)
                    {
                        audio.playClear();
                    }
                }
                break;
            case GameAction::TogglePause:
                game.togglePause();
                break;
            case GameAction::Restart:
                if (game.isGameOver())
                {
                    game.reset();
                }
                break;
        }
    }
}

int main(int argc, char **argv)
{
    const char *executablePath = argc > 0 ? argv[0] : nullptr;
    const ResourcePaths resourcePaths(executablePath);

    InitWindow(kWindowWidth, kWindowHeight, "Tetris by C++");
    SetTargetFPS(kTargetFPS);

    {
        RaylibRenderer renderer(resourcePaths);
        AudioService audio(resourcePaths);
        InputController input;
        Game game;

        while (!WindowShouldClose())
        {
            audio.updateMusic();

            if (const auto action = input.pollAction())
            {
                applyAction(*action, game, audio);
            }

            if (eventTriggered(game.dropIntervalSeconds()))
            {
                const auto result = game.tickDown();
                if (result.linesCleared > 0)
                {
                    audio.playClear();
                }
            }

            renderer.draw(game);
        }
    }

    CloseWindow();
    return 0;
}
