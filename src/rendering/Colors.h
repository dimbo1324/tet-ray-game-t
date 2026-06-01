#ifndef COLORS_H
#define COLORS_H

#include <raylib.h>
#include <vector>

namespace tetris
    {
        // Объявляем цвета как внешние константы
        extern const Color kDarkGrey;
        extern const Color kGreen;
        extern const Color kRed;
        extern const Color kOrange;
        extern const Color kYellow;
        extern const Color kPurple;
        extern const Color kCyan;
        extern const Color kBlue;
        extern const Color kLightBlue;
        extern const Color kDarkBlue;

        // Функция для получения набора цветов ячеек (индекс 0 — пустая ячейка)
        std::vector<Color> GetCellColors();
    }

#endif // COLORS_H
