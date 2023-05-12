#include "Game.h"

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
TTF_Font *gFont = NULL;

Texture Blocks[7];
Texture Full_Piece[7];

Texture Background;
Texture Main_Board;
Texture Next_Piece;
Texture Hold_Piece;
Texture Score_Board;

Texture Score;

Texture Game_Over;


//Basic Initialization_____________________________________________________________________________________________
bool init();

bool loadMedia();

void close();

//Render____________________________________________________________________________________________________________
void render_game(const Game* game);

void render_background();
void render_board(Game *game);
void draw_piece(Piece *piece);
void draw_next_piece(Game* game);
void draw_hold_piece(Game* game);

void render_block(int value, int board_row, int board_col);

void render_score(Game *game);

//Logic_____________________________________________________________________________________________________________
void update_game(Game* game, Game_input* input);

void update_game_play(Game* game, Game_input* input);

void update_game_line(Game *game);

void update_game_over(Game *game);

void handle_keyboard(Game_input *input);


//Basic Initialization_____________________________________________________________________________________________
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "My tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH * BLOCK_SIZE, SCREEN_HEIGHT * BLOCK_SIZE, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				//Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}

				 //Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
    bool success = true;

	//Open the font
	gFont = TTF_OpenFont( "Fonts/BungeeShade.ttf", 31 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
	}

    for(int i = 0; i < 7; ++i)
    {
        if(!Blocks[i].loadFromFile(Block_Path[i], gRenderer))
        {
            std::cout << "Cannot load Block image" << std::endl;
            success = false;
        }
    }

    for(int i = 0; i < 7; ++i)
    {
        if(!Full_Piece[i].loadFromFile(Piece_Path[i], gRenderer))
        {
            std::cout << "Cannot load Piece image" << std::endl;
            success = false;
        }
    }

    if(!Background.loadFromFile(Background_Path, gRenderer))
    {
        std::cout << "Cannot load Background image" << std::endl;
        success = false;
    }

    if(!Main_Board.loadFromFile(Main_Board_Path, gRenderer))
    {
        std::cout << "Cannot load Main Board image" << std::endl;
        success = false;
    }

    if(!Next_Piece.loadFromFile(Next_Piece_Path, gRenderer))
    {
        std::cout << "Cannot load Next Piece image" << std::endl;
        success = false;
    }

    if(!Hold_Piece.loadFromFile(Hold_Piece_Path, gRenderer))
    {
        std::cout << "Cannot load Hold Piece image" << std::endl;
        success = false;
    }

    if(!Score_Board.loadFromFile(Score_Path, gRenderer))
    {
        std::cout << "Cannot load Score image" << std::endl;
        success = false;
    }

    if(!Game_Over.loadFromFile(Game_Over_Path, gRenderer))
    {
        std::cout << "Cannot load Game Over image" << std::endl;
        success = false;
    }

    return success;
}

void close()
{
    for(int i = 0; i < 7; ++i)
    {
        Blocks[i].free();
        Full_Piece[i].free();
    }

    Background.free();
    Main_Board.free();

    Next_Piece.free();
    Hold_Piece.free();
    Score_Board.free();

    Score.free();

    //Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;

    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);
    gWindow = NULL;
	gRenderer = NULL;

    //Quit IMG and SDL
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}

//Logic_____________________________________________________________________________________________________________
void update_game(Game* game, Game_input* input)
{
    switch(game->status)
    {
    case GAME_PLAY:
        update_game_play(game, input);
        break;

    case GAME_HIGHLIGHT_LINE:
        update_game_line(game);
        break;

    case GAME_OVER:
        update_game_over(game);
        break;
    }
}

void update_game_play(Game* game, Game_input* input)
{
    Piece back_up = game->piece;

    if(input->left_status > 0)
    {
        back_up.offset_col--;
    }

    if(input->right_status > 0)
    {
        back_up.offset_col++;
    }

    if(input->up_status > 0)
    {
        back_up.rotation = (back_up.rotation + 1) % 4;
    }

    if(input->space_status > 0)
    {
        back_up = game->hold_piece;
    }

    if(game->check_piece_valid(&back_up))
    {
        if(input->space_status > 0)
        {
            if(game->hold_piece.tetrimino_index == -1)
            {
                back_up.tetrimino_index = game->pick_a_random_number_for_next_piece();
            }
            game->hold_piece = game->piece;

            back_up.offset_col = game->piece.offset_col;
            back_up.offset_row = game->piece.offset_row;
        }

        game->piece = back_up;
    }

    if(input->down_status > 0)
    {
        game->soft_drop();
    }

    if(input->enter_status > 0)
    {
        while(game->soft_drop());
    }

    while(game->real_time >= game->next_drop_time)
    {
        game->soft_drop();
    }

    if(game->check_rows_filled() > 0)
    {
        game->current_cleared_lines = game->count_filled_lines() - 1;        
        game->highlight_end_time = game->real_time + 0.2;
        game->status = GAME_HIGHLIGHT_LINE;         
    }

    if(game->is_over())
    {
        game->before_end_time = game->real_time + 0.5;
        game->status = GAME_OVER;
    }
}

void update_game_line(Game *game)
{
    if(game->real_time >= game->highlight_end_time)
    {
        game->empty_rows_filled();
        game->cleared_lines_count += game->current_cleared_lines;

        //if (game->cleared_lines_count >= game->get_lines_for_next_level() && game->level < 29) game->level++;

        game->point += game->calculate_game_point();
        game->status = GAME_PLAY;
    }
}

void update_game_over(Game *game)
{
    if(game->real_time > game->before_end_time)
    {
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderClear(gRenderer);
        
        Game_Over.render(0, 0, gRenderer);

        SDL_RenderPresent(gRenderer);
    }
}

void handle_keyboard(Game_input *input)
{
    Game_input pre_input = *input;

    int key_number;
    const Uint8 *key_states  = SDL_GetKeyboardState(&key_number);

    input->left = key_states[SDL_SCANCODE_LEFT];
    input->right = key_states[SDL_SCANCODE_RIGHT];
    input->up = key_states[SDL_SCANCODE_UP];
    input->down = key_states[SDL_SCANCODE_DOWN];
    input->enter = key_states[SDL_SCANCODE_RETURN];
    input->space = key_states[SDL_SCANCODE_SPACE];

    input->left_status = input->left - pre_input.left;
    input->right_status = input->right - pre_input.right;
    input->up_status = input->up - pre_input.up;
    input->down_status = input->down - pre_input.down;
    input->enter_status = input->enter - pre_input.enter;
    input->space_status = input->space - pre_input.space;
}

//Render____________________________________________________________________________________________________________

void render_game(Game* game)
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gRenderer);

    render_background();

    render_board(game);

    draw_next_piece(game);

    draw_hold_piece(game);

    draw_piece(&game->piece);

    render_score(game);

    SDL_RenderPresent(gRenderer);
}

void render_background()
{
    Background.render(0, 0, gRenderer);
    Main_Board.render( (SCREEN_WIDTH * BLOCK_SIZE - BOARD_WIDTH * BLOCK_SIZE) / 2, (SCREEN_HEIGHT * BLOCK_SIZE - VISIBLE_HEIGHT * BLOCK_SIZE) / 2, gRenderer);

    Next_Piece.render( (SCREEN_WIDTH * BLOCK_SIZE - BOARD_WIDTH * BLOCK_SIZE) / 2 + BLOCK_SIZE * 14, (SCREEN_HEIGHT * BLOCK_SIZE - VISIBLE_HEIGHT * BLOCK_SIZE) / 2, gRenderer);
    Hold_Piece.render( (SCREEN_WIDTH * BLOCK_SIZE - BOARD_WIDTH * BLOCK_SIZE) / 2 + BLOCK_SIZE * 14, (SCREEN_HEIGHT * BLOCK_SIZE - VISIBLE_HEIGHT * BLOCK_SIZE) / 2 + BLOCK_SIZE * 12, gRenderer);
    
    Score_Board.render( (SCREEN_WIDTH * BLOCK_SIZE - BOARD_WIDTH * BLOCK_SIZE) / 2 - BLOCK_SIZE * 10, (SCREEN_HEIGHT * BLOCK_SIZE - VISIBLE_HEIGHT * BLOCK_SIZE) / 2, gRenderer);
}

void render_board(Game *game)
{
    for(int i = BOARD_HEIGHT - VISIBLE_HEIGHT; i < BOARD_HEIGHT; ++i)
    {
        for(int j = 0; j < BOARD_WIDTH; ++j)
        {
            int value = get_data_value(game->board, BOARD_WIDTH, i, j);

            if(value > 0)
            {
                render_block(value - 1, i, j);
            }
        }
    }
}

void draw_piece(Piece *piece)
{
    Tetrimino tetrimino = TETRIMINOS[piece->tetrimino_index];

    for(int i = 0; i < tetrimino.side; ++i)
    {
        for(int j = 0; j < tetrimino.side; ++j)
        {
            int value = tetrimino.tetrimino_get(i, j, piece->rotation);

            if(value > 0)
            {
                if(piece->offset_row + i >= 1)
                {
                    if(piece->offset_row + i >= BOARD_HEIGHT - VISIBLE_HEIGHT)
                    {
                        render_block(piece->tetrimino_index, piece->offset_row + i, piece->offset_col + j);
                    }
                }
            }
        }
    }
}

void draw_next_piece(Game* game)
{
    int index = game->next_piece.tetrimino_index;

    int x = (SCREEN_WIDTH * BLOCK_SIZE - BOARD_WIDTH * BLOCK_SIZE) / 2 + BLOCK_SIZE * 14;
    int y = (SCREEN_HEIGHT * BLOCK_SIZE - VISIBLE_HEIGHT * BLOCK_SIZE) / 2;

    Full_Piece[index].render(x + (150 - Full_Piece[index].getWidth()) / 2, y + (200 - Full_Piece[index].getHeight()) / 2, gRenderer);
}

void draw_hold_piece(Game* game)
{
    int index = game->hold_piece.tetrimino_index;

    int x = (SCREEN_WIDTH * BLOCK_SIZE - BOARD_WIDTH * BLOCK_SIZE) / 2 + BLOCK_SIZE * 14;
    int y = (SCREEN_HEIGHT * BLOCK_SIZE - VISIBLE_HEIGHT * BLOCK_SIZE) / 2 + BLOCK_SIZE * 12;

    Full_Piece[index].render(x + (150 - Full_Piece[index].getWidth()) / 2, y + (200 - Full_Piece[index].getHeight()) / 2, gRenderer);
}

void render_block(int value, int board_row, int board_col)
{
    int x = (SCREEN_WIDTH * BLOCK_SIZE - BOARD_WIDTH * BLOCK_SIZE) / 2 + (board_col * BLOCK_SIZE);
    int y = (SCREEN_HEIGHT * BLOCK_SIZE - BOARD_HEIGHT * BLOCK_SIZE) / 2 + ( (board_row - 1) * BLOCK_SIZE);

    Blocks[value].render( x, y, gRenderer);
}

void render_score(Game *game)
{
    //Render text
    SDL_Color white = { 255, 255, 255 };
    if( !Score.loadFromRenderedText( std::to_string(game->point), white, gRenderer, gFont ) )
    {
        printf( "Failed to render score texture!\n" );
    }
    else
    {
        int x = (SCREEN_WIDTH * BLOCK_SIZE - BOARD_WIDTH * BLOCK_SIZE) / 2 - BLOCK_SIZE * 10;
        int y = (SCREEN_HEIGHT * BLOCK_SIZE - VISIBLE_HEIGHT * BLOCK_SIZE) / 2;

        Score.render( x + (150 - Score.getWidth()) / 2, y + (200 - Score.getHeight()) / 2, gRenderer);
    }
}


int main(int argc, char* args[])
{
    
    Game game = {};

    game.spawn_new_piece();

    Game_input input = {};

    if(!init())
    {
        std::cout << "Cannot initialize" << std::endl;
    }
    else
    {
        if(!loadMedia())
        {
            std::cout << "Cannot load medias" << std::endl;
        }
        else
        {
            SDL_Event e;

            bool quit = false;

            while(!quit)
            {
                while(SDL_PollEvent(&e) != 0)
                {
                    if(e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }

                game.real_time = SDL_GetTicks() / 1000.0f;

                handle_keyboard(&input);

                update_game(&game, &input);

                if(game.is_over())
                {
                    continue;
                }

                render_game(&game);

            }
        }

    }

    close();

    return 0;
}
