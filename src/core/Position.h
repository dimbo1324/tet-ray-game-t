#ifndef POSITION_H
#define POSITION_H

namespace tetris
    {
        class Position
            {
            public:
                Position(int row, int col);

                int row;
                int col;
            };
    } // namespace tetris

#endif // POSITION_H
