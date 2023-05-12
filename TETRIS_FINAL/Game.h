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
    Piece next_piece;
    Piece hold_piece;
    //Piece next_piece;

    long long int point;

    double real_time;
    double next_drop_time;
    double highlight_end_time;
    double before_end_time;

    int level;
    int start_level;

    int filled[BOARD_HEIGHT];
    int cleared_lines_count;
    int current_cleared_lines;

//constructor___________________________________________________________________________________________________________
    Game();

//logic of the game_____________________________________________________________________________________________________

    long long int calculate_game_point();
    bool is_over(); 

    int count_filled_lines();
    //int get_lines_for_next_level();
    int pick_a_random_number_for_next_piece();
    
    bool check_piece_valid(Piece* pPiece);
    bool soft_drop();
    void merge_piece_to_board();
    void spawn_new_piece();
    double get_time_to_next_drop();

    void empty_rows_filled();
    int check_rows_filled();   

};

#endif