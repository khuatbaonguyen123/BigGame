#ifndef GAME_H
#define GAME_H

#include "Piece.h"
#include "Tetrimino.h"
#include "Texture.h"

class Game
{
public:

    int board[BOARD_WIDTH * BOARD_HEIGHT] = {0};
    GAME_STATUS status;
    Piece piece;

//constructor___________________________________________________________________________________________________________
    Game(GAME_STATUS pStatus, Piece pPiece);

//logic of the game_____________________________________________________________________________________________________

    bool check_piece_valid(Piece pPiece);
};

#endif