#include "InputController.h"

#include <raylib.h>

namespace tetris
{
    std::optional<GameAction> InputController::pollAction() const
    {
        int key = GetKeyPressed();
        switch (key)
        {
            case KEY_LEFT:
                return GameAction::MoveLeft;
            case KEY_RIGHT:
                return GameAction::MoveRight;
            case KEY_DOWN:
                return GameAction::SoftDrop;
            case KEY_UP:
                return GameAction::Rotate;
            case KEY_SPACE:
                return GameAction::HardDrop;
            case KEY_ENTER:
                return GameAction::Restart;
            case KEY_P:
            case KEY_ESCAPE:
                return GameAction::TogglePause;
            default:
                return std::nullopt;
        }
    }
}
