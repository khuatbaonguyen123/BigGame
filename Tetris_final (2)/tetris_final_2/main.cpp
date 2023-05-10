#include "Game.h"

//input class for handling keyboard
class Game_input {
public:
    int left;
    int right;
    int up;
    int down;

    //while the value of status is greater than 0, it means they are pressed
    int left_status;
    int right_status;
    int down_status;
    int up_status;

    //constructor
    Game_input()
    {
        int left = 0;
        int right = 0;
        int up = 0;
        int down = 0;

        //while the value of status is greater than 0, it means they are pressed
        int left_status = 0;
        int right_status = 0;
        int down_status = 0;
        int up_status = 0;  
    }
};

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

GAME_STATUS status;
Game_input input = Game_input();

Piece piece = Piece();
Game game = Game(status, piece);

Texture Blocks[7];
Texture Background;
Texture Main_Board;


//Basic Initialization_____________________________________________________________________________________________
bool init();

bool loadMedia();

void close();

//Render____________________________________________________________________________________________________________
void render_game();

void render_background();
void render_board();
void draw_piece(Piece pPiece);

void render_block(Texture block, int board_row, int board_col);

//Logic_____________________________________________________________________________________________________________
void update_game(Game pGame);

void update_game_play(Game pGame);

void handle_keyboard(Game_input pInput);


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

    for(int i = 0; i < 7; ++i)
    {
        if(!Blocks[i].loadFromFile(Block_Path[i], gRenderer))
        {
            std::cout << "Cannot load Block image" << std::endl;
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

    return success;
}

void close()
{
    for(int i = 0; i < 7; ++i)
    {
        Blocks[i].free();
    }

    Background.free();
    Main_Board.free();

    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);

    //Quit IMG and SDL
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    Mix_Quit();
}

//Render____________________________________________________________________________________________________________
void render_game()
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gRenderer);

    render_background();
    render_board();
    draw_piece(piece);

    SDL_RenderPresent(gRenderer);
}

void render_background()
{
    Background.render(0, 0, gRenderer);
    Main_Board.render( (SCREEN_WIDTH * BLOCK_SIZE - BOARD_WIDTH * BLOCK_SIZE) / 2, (SCREEN_HEIGHT * BLOCK_SIZE - VISIBLE_HEIGHT * BLOCK_SIZE) / 2, gRenderer);
}

void render_board()
{
    for(int i = BOARD_HEIGHT - VISIBLE_HEIGHT; i < BOARD_HEIGHT; ++i)
    {
        for(int j = 0; j < BOARD_WIDTH; ++j)
        {
            int value = get_data_value(game.board, BOARD_WIDTH, i, j);
            if(value)
            {
                render_block(Blocks[value - 1], i, j);
            }
        }
    }
}

void draw_piece(Piece pPiece)
{
    Tetrimino tetrimino = TETRIMINOS[pPiece.tetrimino_index];

    for(int i = 0; i < tetrimino.side; ++i)
    {
        for(int j = 0; j < tetrimino.side; ++j)
        {
            int value = tetrimino.tetrimino_get(i, j, piece.rotation);

            if(value > 0)
            {
                int board_row = piece.offset_row + i;
                int board_col = piece.offset_col + j;

                render_block(Blocks[pPiece.tetrimino_index], board_row, board_col);
            }
        }
    }
}

void render_block(Texture block, int board_row, int board_col)
{
    int x = (SCREEN_WIDTH * BLOCK_SIZE - BOARD_WIDTH * BLOCK_SIZE) / 2 + board_col * BLOCK_SIZE;
    int y = (SCREEN_HEIGHT * BLOCK_SIZE - BOARD_HEIGHT * BLOCK_SIZE) / 2 + board_row * BLOCK_SIZE;

    block.render(x, y, gRenderer);
}

//Logic_____________________________________________________________________________________________________________
void update_game(Game pGame)
{
    switch(status)
    {
    case GAME_PLAY:
        update_game_play(pGame);
        break;
    }
}

void update_game_play(Game pGame)
{
    Piece back_up = piece;

    if(input.down_status > 0)
    {
        back_up.offset_row++;
    }

    if(input.right_status > 0)
    {
        back_up.offset_col++;
    }

    if(input.left_status > 0)
    {
        back_up.offset_col--;
    }

    if(input.up_status > 0)
    {
        back_up.rotation = (back_up.rotation + 1) % 4;
    }

    if(pGame.check_piece_valid(back_up))
    {
        piece = back_up;
    }
}

void handle_keyboard(Game_input pInput)
{
    //Get Key Board State to update into input;
    Game_input pre_input = pInput;

    int key_number;
    const Uint8 *key_states  = SDL_GetKeyboardState(&key_number);

    pInput.left = key_states[SDL_SCANCODE_LEFT];
    pInput.right = key_states[SDL_SCANCODE_RIGHT];
    pInput.up = key_states[SDL_SCANCODE_UP];
    pInput.down = key_states[SDL_SCANCODE_DOWN];

    pInput.left_status = pInput.left - pre_input.left;
    pInput.right_status = pInput.right - pre_input.right;
    pInput.up_status = pInput.up - pre_input.up;
    pInput.down_status = pInput.down - pre_input.down;
}


int main(int argc, char* args[])
{
    piece.tetrimino_index = 2;
    
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

                render_game();

                handle_keyboard(input);

                update_game_play(game);
            }
        }

    }

    close();

    return 0;
}
