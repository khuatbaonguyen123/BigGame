#include "Game.h"

Game::Game(GAME_STATUS pStatus, Piece* pPiece, Game_input* pInput, SDL_Renderer* renderer)
{
    mStatus = pStatus;
    mPiece = pPiece;
    mInput = pInput;
    mRenderer = renderer;
}

Game::~Game()
{
    //just free memories
}

void Game::update_game()
{
    switch(mStatus)
    {
    case GAME_PLAY:
        update_game_play();
        break;
    }
}

void Game::update_game_play()
{
    Piece* clone_piece = mPiece;
    
    if(mInput->down_status > 0)
    {
        clone_piece->offset_row++;
    }

    if(mInput->right_status > 0)
    {
        clone_piece->offset_col++;
    }

    if(mInput->left_status > 0)
    {
        clone_piece->offset_col--;
    }

    if(mInput->up_status > 0)
    {
        clone_piece->rotation = (clone_piece->rotation + 1) % 4;
    }

    if(check_piece_valid(clone_piece))
    {
        mPiece = clone_piece;
    }
}

bool Game::check_piece_valid(Piece* piece_clone)
{
    Tetrimino tetrimino = TETRIMINOS[piece_clone->tetrimino_index];

    for(int row = 0; row < tetrimino.side; ++row)
    {
        for(int col = 0; col < tetrimino.side; ++col)
        {
            int value = tetrimino.tetrimino_value_get(row, col, piece_clone->rotation);// 1, 2, or 3, etc

            if(value) // we only have to care about the cell with value greater than 0
            {
                int board_row = piece_clone->offset_row + row;
                int board_col = piece_clone->offset_col + col;
                if(board_row < 0 || board_col < 0 || board_row >= BOARD_HEIGHT || board_col >= BOARD_WIDTH)
                {
                    return false;
                }

                if(get_data_value(board, BOARD_WIDTH, board_row, board_col))
                {
                    return false;
                }
            }
        }
    }

    return true;

}

void Game::handle_keyboard()
{
    //Get Key Board State to update into input;
    Game_input* pre_input = mInput;

    int key_number;
    const Uint8 *key_states  = SDL_GetKeyboardState(&key_number);

    mInput->left = key_states[SDL_SCANCODE_LEFT];
    mInput->right = key_states[SDL_SCANCODE_RIGHT];
    mInput->up = key_states[SDL_SCANCODE_UP];
    mInput->down = key_states[SDL_SCANCODE_DOWN];

    mInput->left_status = mInput->left - pre_input->left;
    mInput->right_status = mInput->right - pre_input->right;
    mInput->up_status = mInput->up - pre_input->up;
    mInput->down_status = mInput->down - pre_input->down;
}

void Game::render_game()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);
    
    render_background_images(Background_Path, Main_Board_Path);
    draw_piece(mPiece);

    SDL_RenderPresent(mRenderer);
}

void Game::render_background_images(std::string bkg_path, std::string main_board_path)
{
    Texture Background, Main_Board;

    if(!Background.loadFromFile(bkg_path, mRenderer) || !Main_Board.loadFromFile(main_board_path, mRenderer))
    {
        std::cout << "Cannot load background images" << std::endl;
    }

    else
    {
        Background.render(0, 0, mRenderer);
        Main_Board.render( (SCREEN_WIDTH - BOARD_WIDTH * BLOCK_SIZE) / 2, (SCREEN_HEIGHT - VISIBLE_HEIGHT * BLOCK_SIZE) / 2, mRenderer);
    }

}

void Game::render_block(std::string path, int board_row, int board_col)
{
    int x = (SCREEN_WIDTH - BOARD_WIDTH * BLOCK_SIZE) / 2 + BLOCK_SIZE * board_col;
    int y = (SCREEN_HEIGHT - BOARD_HEIGHT * BLOCK_SIZE) / 2 + BLOCK_SIZE * board_row;

    Texture block;

    if(!block.loadFromFile(path, mRenderer))
    {
        std::cout << "Can not load tetrimino picture" << std::endl;
    }
    else
    {
        block.render(x, y, mRenderer);
    }
}

void Game::draw_piece(Piece* piece)
{
    int value = piece->tetrimino_index;
    Tetrimino tetri = TETRIMINOS[value];

    for(int row = 0; row < tetri.side; ++row)
    {
        for(int col = 0; col < tetri.side; ++col)
        {
            if(tetri.tetrimino_value_get(row, col, piece->rotation))
            {
                int board_row = piece->offset_row + row;
                int board_col = piece->offset_col + col;

                if(board_row >= BOARD_HEIGHT - VISIBLE_HEIGHT)
                {
                    render_block(Block_Paths[value], board_row, board_col);
                }
            }

        }
    }
}
