#include "Piece.h"

Tetrimino::~Tetrimino()
{
    //do nothing
}

int Tetrimino::tetrimino_value_get(int row, int col, int rotation)
{
    switch(rotation) {
        case 0:
            return data[side * row + col];
        case 1:
            return data[side * (side - col - 1) + row];
        case 2:
            return data[side * (side - row - 1) + (side - col - 1)];
        case 3:
            return data[side * col + (side - row - 1)];
    }

    return 0;
}

Piece::Piece()
{
    tetrimino_index = -1;
    offset_row = 0;
    offset_col = BOARD_WIDTH/2;
    rotation = 0;
}

Piece::~Piece()
{
    //do nothing
}
