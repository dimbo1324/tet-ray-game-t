#ifndef TETRIS_CORE_TETROMINO_TYPE_H
#define TETRIS_CORE_TETROMINO_TYPE_H

#include <array>
#include <cstddef>

namespace tetris
{
    enum class TetrominoType
    {
        Empty = 0,
        I,
        J,
        L,
        O,
        S,
        T,
        Z
    };

    constexpr std::array<TetrominoType, 7> kTetrominoTypes = {
        TetrominoType::I, TetrominoType::J, TetrominoType::L, TetrominoType::O,
        TetrominoType::S, TetrominoType::T, TetrominoType::Z};

    constexpr std::size_t toCellIndex(TetrominoType type)
    {
        return static_cast<std::size_t>(type);
    }
}

#endif
