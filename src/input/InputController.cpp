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
                return GameAction::MoveDown;
            case KEY_UP:
                return GameAction::Rotate;
            case KEY_SPACE:
            case KEY_ENTER:
                return GameAction::Restart;
            default:
                return std::nullopt;
        }
    }
}
