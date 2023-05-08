#ifndef GAME_H
#define GAME_H

#include "Common.h"
#include "Texture.h"

class Game
{
public:
    Game(GAME_STATUS pStatus, Piece* pPiece, Game_input* pInput, SDL_Renderer* renderer);
    ~Game();

    int board[BOARD_WIDTH * BOARD_HEIGHT] = {0};

    void update_game();
    void update_game_play();

    bool check_piece_valid(Piece* piece_clone);
    void handle_keyboard();

//render___________________________________________________________________________________________________________

    void render_game();
    void render_background_images(std::string bkg_path, std::string main_board_path);
    void render_block(std::string path, int board_row, int board_col);
    void draw_piece(Piece* piece);

private:
    
    GAME_STATUS mStatus;
    Piece *mPiece;
    Game_input* mInput;
    SDL_Renderer* mRenderer;
};

#endif