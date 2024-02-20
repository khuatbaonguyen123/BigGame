#include "Game.h"

Game::Game()
{
    status = GAME_ON_MENU;
    level = 0;
    start_level = 0;
    spawn_piece_count = 0;

    cleared_lines_count = 0;
    current_cleared_lines = 0;

    point = 0; 
    record_point = 0;

    music_on = true;
    audio_on = true;

    game_quit = false;
}

void Game::reset()
{
    level = 0;
    spawn_piece_count = 0;

    cleared_lines_count = 0;
    current_cleared_lines = 0;

    point = 0; 
    //record_point = 0;

    for(int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; ++i)
    {
        board[i] = 0;
    }

    spawn_new_piece();

    hold_piece.tetrimino_index = -1;
}

long long int Game::calculate_game_point()
{
    if(current_cleared_lines == 1)
    {
        return 40 * (level + 1);
    }

    if(current_cleared_lines == 2)
    {
        return 100 * (level + 1);
    }

    if(current_cleared_lines == 3)
    {
        return 200 * (level + 1);
    }

    if(current_cleared_lines == 4)
    {
        return 300 * (level + 1);
    }

    return 0;
}

void Game::get_record()
{
    std::ifstream Record_File("Score.txt");

    if(Record_File.is_open())
    {
        int record;

        while(Record_File >> record);

        Record_File.close();

        record_point = record;

        if(point > record_point)
        {
            std::ofstream File("Score.txt");
            if(File.is_open())
            {
                File << point << std::endl;
                record_point = point;
            }

            File.close();
        }
    }
    else
    {
        std::cout << "Cannot open file" << std::endl;
    }
}

bool Game::is_over()
{
    for(int j = BOARD_WIDTH - 1; j >=  0; j--)
    {
        int value = get_data_value(board, BOARD_WIDTH, 2, j);

        if(value > 0)
        {
            return true;
        }
    }

    return false;     
}

/***
    return a number of lines people has just filled at the moment
***/
int Game::count_filled_lines() {
    int count = 0;
    for(int i : filled) 
    {
        if( i > 0 ) 
        {
            count++;
        }
    }
    
    return count;
}

int Game::pick_a_random_number_for_next_piece()
{
    int index = piece.tetrimino_index;

    srand ((unsigned int) time(NULL));
    int result = get_random_number(0,6);
    if( result == index)
    {
        result = ( result + get_random_number(0,6) ) % 7;
    }
    return result;
}

bool Game::check_piece_valid(Piece* pPiece)
{
    Tetrimino tetrimino = TETRIMINOS[pPiece->tetrimino_index];

    for(int i = 0; i < tetrimino.side; ++i)
    {
        for(int j = 0; j < tetrimino.side; ++j)
        {
            int value = tetrimino.tetrimino_get(i, j, pPiece->rotation);

            if(value > 0)
            {
                int current_row = pPiece->offset_row + i;
                int current_col = pPiece->offset_col + j;

                if(current_row < 0 || current_col < 0 || current_row > VISIBLE_HEIGHT + 1 || current_col >= BOARD_WIDTH)
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

bool Game::soft_drop()
{
    bool success = true;

    ++piece.offset_row;

    if(!check_piece_valid(&piece))
    {
        --piece.offset_row;
        success = false;
        merge_piece_to_board();
        spawn_new_piece();
    }

    next_drop_time = real_time + get_time_to_next_drop();

    return success;
}

void Game::merge_piece_to_board()
{
    Tetrimino tetrimino = TETRIMINOS[piece.tetrimino_index];

    for(int i = 0; i < tetrimino.side; ++i)
    {
        for(int j = 0; j < tetrimino.side; ++j)
        {
            int value = tetrimino.tetrimino_get(i, j, piece.rotation);

            if(value > 0)
            {
                set_data_value(board, BOARD_WIDTH, piece.offset_row + i, piece.offset_col + j, value);
            }
        }
    }
}

void Game::spawn_new_piece()
{
    if(next_piece.tetrimino_index == -1) {
        srand ((unsigned int) time(NULL));
        int random_piece = get_random_number(0,6);
        piece.tetrimino_index = random_piece;
        next_piece.tetrimino_index = pick_a_random_number_for_next_piece();
    }
    else {
        int next_index = pick_a_random_number_for_next_piece();
        piece.tetrimino_index = next_piece.tetrimino_index;
        next_piece.tetrimino_index = next_index;
    }

    piece.offset_row = 0;
    piece.offset_col = BOARD_WIDTH / 2 - 1;

    empty_piece = piece;

    get_pieces_for_each_level();

    spawn_piece_count++;

    level = spawn_piece_count / 10;
}

double Game::get_time_to_next_drop()
{
    if(level > 29)
    {
        level = 29;
    }

    float second_per_frame = 1.0 / 60.0;

    return DROP_FRAMES_PER_LEVEL[level] * second_per_frame;
}

void Game::empty_rows_filled()
{
    if(check_rows_filled() > 0)
    {
        int source_row = BOARD_HEIGHT - 1;

        int temp_board[BOARD_WIDTH * BOARD_HEIGHT] = {0};

        for(int i = source_row; i >= BOARD_HEIGHT - VISIBLE_HEIGHT; i--)
        {
            if(filled[i] == 0)
            {
                for(int j = BOARD_WIDTH - 1; j >= 0; j--)
                {
                    int value = get_data_value(board, BOARD_WIDTH, i, j);
                    set_data_value(temp_board, BOARD_WIDTH, source_row, j, value);
                }
                source_row--;
            }
        }
        
        copyMatrix(temp_board, board, BOARD_HEIGHT, BOARD_WIDTH);
    }
    
}

/***
    - filled: matrix present status of row, 1 is filled row, 0 is unfilled row
    - return number of rows has filled
 ***/
int Game::check_rows_filled() {
    int filled_line_count = 0;
    for(int i = BOARD_HEIGHT - 1; i >= (BOARD_HEIGHT - VISIBLE_HEIGHT); i--)
    {
        int count = 0;
        for(int j = BOARD_WIDTH - 1; j >=  0; j--) {
            if( get_data_value(board, BOARD_WIDTH , i, j) ) count++;
            else break;
        }
        if(count == BOARD_WIDTH) {
            filled[i] = 1;
            filled_line_count++;
        }
        else filled[i] = 0;
    }

    return filled_line_count;
}

void Game::get_pieces_for_each_level()
{
    switch(start_level)
    {
    case 0:
        if(spawn_piece_count > 60)
        {
            spawn_piece_count = 60;
        }
        break;
    
    case 1:
        if(spawn_piece_count < 60)
        {
            spawn_piece_count = 60;
        }

        if(spawn_piece_count > 140)
        {
            spawn_piece_count = 140;
        }
        break;

    case 2: 
        if(spawn_piece_count < 140)
        {
            spawn_piece_count = 140;
        }

        if(spawn_piece_count > 290)
        {
            spawn_piece_count = 290;
        }
        break;
    }
}