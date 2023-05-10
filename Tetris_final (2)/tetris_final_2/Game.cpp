#include "Game.h"

Game::Game(GAME_STATUS pStatus, Piece pPiece)
{
    status = pStatus;
    piece = pPiece;
}

bool Game::check_piece_valid(Piece pPiece)
{
    Tetrimino tetrimino = TETRIMINOS[pPiece.tetrimino_index];

    for(int i = 0; i < tetrimino.side; ++i)
    {
        for(int j = 0; j < tetrimino.side; ++j)
        {
            int value = tetrimino.tetrimino_get(i, j, pPiece.rotation);

            if(value > 0)
            {
                int current_row = pPiece.offset_row + i;
                int current_col = pPiece.offset_col + j;

                if(current_row < 0 || current_col < 0 || current_row > BOARD_HEIGHT || current_col > BOARD_WIDTH)
                {
                    return false;
                }

                if(get_data_value(board, BOARD_WIDTH, current_row, current_col) > 0)
                {
                    return false;
                }
            }
        }
    }

    return true;
}