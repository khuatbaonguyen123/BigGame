#ifndef PIECE_H
#define PIECE_H

#include "Common.h"

//Value of each block (is 0 or not)
class Tetrimino
{
public:
    const int* data; //the matrix that holds the data
    const int side; //the side of the matrix (3x3, 4x4, etc)

    ~Tetrimino();

    int tetrimino_value_get(int row, int col, int rotation);

};



//Each piece is a matrix of tetriminos (multiple one kinds of tetrimino)
class Piece
{
public:

    Piece();
    ~Piece();

    int tetrimino_index; //type of piece (which tetrimino matrix it is)
    int offset_row; //row in board
    int offset_col; //col in board
    int rotation; //rotation of the piece

};

#endif