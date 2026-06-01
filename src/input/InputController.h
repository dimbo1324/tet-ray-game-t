#ifndef TETRIS_INPUT_INPUT_CONTROLLER_H
#define TETRIS_INPUT_INPUT_CONTROLLER_H

#include <optional>

namespace tetris
{
    enum class GameAction
    {
        MoveLeft,
        MoveRight,
        MoveDown,
        Rotate,
        Restart
    };

    class InputController
    {
    public:
        std::optional<GameAction> pollAction() const;
    };
}

#endif
