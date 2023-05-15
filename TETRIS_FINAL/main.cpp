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
Texture Score_And_Level_Board;
Texture Record_Board;

Texture Score;
Texture End_Game_Score;
Texture Level;
Texture Record;

Texture Game_Over;
Texture Menu;

Texture Setting_Background;
Texture Game_Pause_Background;

Mix_Music* Theme_Music = NULL;

Mix_Chunk* Game_Audio[6] = {NULL};

//Non_texture LButton
LButton Play;
LButton Setting;
LButton Quit;
LButton Resume;
LButton Play_Again;


//Setting Page Buttons
LButton Level_Button;
LButton Audio;
LButton Music;
LButton Home_Icon;
LButton Pause_Icon;

//Basic Initialization_____________________________________________________________________________________________
bool init();

bool loadMedia();

void close();


//Render____________________________________________________________________________________________________________
void render_game_play(Game* game);

void render_background();
void render_board(Game *game);
void draw_piece(Piece *piece);
void draw_next_piece(Game* game);
void draw_hold_piece(Game* game);

void render_block(int value, int board_row, int board_col);

void render_string_objects(Game *game); //score, level, record

//Logic_____________________________________________________________________________________________________________
void update_game(Game* game, Game_input* input);

void update_game_menu(Game* game, Game_input* input);

void update_game_setting(Game* game);

void update_game_play(Game* game, Game_input* input);

void update_game_pause(Game* game);

void update_game_line(Game *game);

void update_game_over(Game *game, Game_input *input);

void handle_keyboard(Game_input *input);

void handle_button(Game* game, SDL_Event* e);

void setting_button_set_up(Game* game);


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

                if( Mix_Init(MIX_INIT_MP3) < 0 )
                {
                    printf( "MP3 could not initialize! SDL Error: %s\n", SDL_GetError() );
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

    if(!Score_And_Level_Board.loadFromFile(Score_And_Level_Path, gRenderer))
    {
        std::cout << "Cannot load Score image" << std::endl;
        success = false;
    }

    if(!Record_Board.loadFromFile(Record_Board_Path, gRenderer))
    {
        std::cout << "Cannot load Record Board image" << std::endl;
        success = false;
    }

    if(!Game_Over.loadFromFile(Game_Over_Path, gRenderer))
    {
        std::cout << "Cannot load Game Over image" << std::endl;
        success = false;
    }

    if(!Menu.loadFromFile(Menu_Path, gRenderer))
    {
        std::cout << "Cannot load Menu image" << std::endl;
        success = false;
    }

    if(!Setting_Background.loadFromFile(Setting_Background_Path, gRenderer))
    {
        std::cout << "Cannot load Setting Background image" << std::endl;
        success = false; 
    }

    if(!Game_Pause_Background.loadFromFile(Game_Pause_Background_Path, gRenderer))
    {
        std::cout << "Cannot load Game Pause Background Image" << std::endl;
        success = false;
    }

    Theme_Music = Mix_LoadMUS(Game_Music_Path.c_str());
    if(Theme_Music == NULL)
    {
        std::cout << "Cannot load theme music" << std::endl;
        success = false;
    }

    for(int i = 0; i < 6; ++i)
    {
        Game_Audio[i] = Mix_LoadWAV(Game_Audio_Path[i].c_str());
        if(Game_Audio[i] == NULL)
        {
            std::cout << "Cannot load sound effect[" << i << "]" << std::endl;
            success = false;
        }
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
    Score_And_Level_Board.free();
    Record_Board.free();
    Score.free();
    End_Game_Score.free();
    Level.free();
    Record.free();
    Game_Over.free();
    Menu.free();
    Setting_Background.free();
    Game_Pause_Background.free();

    Level_Button.free();
    Music.free();
    Audio.free();
    Home_Icon.free();
    Pause_Icon.free();
    Play_Again.free();
    

	//Free the music
	Mix_FreeMusic( Theme_Music );
	Theme_Music = NULL;

    for(int i = 0; i < 6; ++i)
    {
        Mix_FreeChunk(Game_Audio[i]);
        Game_Audio[i] = NULL;
    }
    Mix_CloseAudio();

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
    handle_keyboard(input);

    if(game->music_on)
    {
        if(Mix_PlayingMusic() == 0)
        {
            Mix_PlayMusic(Theme_Music, -1);
        }
        else if(Mix_PausedMusic() == 1)
        {
            Mix_ResumeMusic();
        }

        Mix_VolumeMusic(MIX_MAX_VOLUME/2);
    }
    else
    {
        Mix_PauseMusic();
    }

    game->get_record();
    
    switch(game->status)
    {
    case GAME_ON_MENU:
        update_game_menu(game, input);
        break;

    case GAME_ON_SETTING:
        update_game_setting(game);
        break;
    
    case GAME_PLAY:
        update_game_play(game, input);
        break;

    case GAME_ON_PAUSE:
        update_game_pause(game);
        break;

    case GAME_HIGHLIGHT_LINE:
        update_game_line(game);
        break;

    case GAME_OVER:
        update_game_over(game, input);
        break;
    }
}

void update_game_menu(Game* game, Game_input* input)
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gRenderer);
    
    Menu.render(0, 0, gRenderer);

    SDL_RenderPresent(gRenderer);

    Play.set_button_without_texture(704, 275, 234, 75);
    Setting.set_button_without_texture(606, 381, 429, 75);
    Quit.set_button_without_texture(704, 487, 234, 75);

    if(Play.be_clicked())
    {        
        game->before_start_time = game->real_time + 0.2;
        game->reset();
        game->status = GAME_PLAY;
    }

    if(Setting.be_clicked())
    {
        game->before_start_time = game->real_time + 0.2;
        game->status = GAME_ON_SETTING;
    }

    if(Quit.be_clicked())
    {
        game->game_quit = true;
    }

    Play.update_button_status();
    Setting.update_button_status();
    Quit.update_button_status();
    
}

void update_game_setting(Game *game)
{
    if(game->real_time > game->before_start_time)
    {
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderClear(gRenderer);

        Setting_Background.render(0, 0, gRenderer);

        setting_button_set_up(game);

        Level_Button.render(gRenderer);
        Music.render(gRenderer);
        Audio.render(gRenderer);
        Home_Icon.render(gRenderer);

        SDL_RenderPresent(gRenderer);

    }
}

void update_game_play(Game* game, Game_input* input)
{
    if(game->real_time > game->before_start_time)
    {
        Piece back_up = game->piece;

        if(input->left_status > 0)
        {
            back_up.offset_col--;
            if(game->audio_on)
            {
                Mix_PlayChannel(-1, Game_Audio[MOVE], 0);
            }
        }

        if(input->right_status > 0)
        {
            back_up.offset_col++;
            if(game->audio_on)
            {
                Mix_PlayChannel(-1, Game_Audio[MOVE], 0);
            }
        }

        if(input->up_status > 0)
        {
            back_up.rotation = (back_up.rotation + 1) % 4;
            if(game->audio_on)
            {
                Mix_PlayChannel(-1, Game_Audio[ROTATE], 0);
            }
        }

        if(input->space_status > 0)
        {
            back_up = game->hold_piece;
             if(game->audio_on)
            {
                Mix_PlayChannel(-1, Game_Audio[ROTATE], 0);
            }
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
            if(game->audio_on)
            {
                Mix_PlayChannel(-1, Game_Audio[MOVE], 0);
            }
        }

        if(input->enter_status > 0)
        {
            while(game->soft_drop())
            {
                if(game->audio_on)
                {
                    Mix_PlayChannel(-1, Game_Audio[DROP], 0);
                }
            }

        }

        while(game->real_time >= game->next_drop_time)
        {
            game->soft_drop();
            if(game->audio_on)
            {
                Mix_PlayChannel(-1, Game_Audio[DROP], 0);
            }
        }

        if(game->check_rows_filled() > 0)
        {
            game->current_cleared_lines = game->check_rows_filled();        
            game->highlight_end_time = game->real_time + 0.2;
            game->status = GAME_HIGHLIGHT_LINE;         
        }

        Pause_Icon.set_up(Button_Path[PAUSE_ICON], (SCREEN_WIDTH * BLOCK_SIZE - BOARD_WIDTH * BLOCK_SIZE) / 2 + BLOCK_SIZE * 14 + 35, (SCREEN_HEIGHT * BLOCK_SIZE - VISIBLE_HEIGHT * BLOCK_SIZE) / 2 + BLOCK_SIZE * 9 - 25, gRenderer);

        if(Pause_Icon.be_clicked())
        {
            game->status = GAME_ON_PAUSE;
        }

        Pause_Icon.update_button_status();

        if(game->is_over())
        {
            game->before_end_time = game->real_time + 0.5;
            if(game->audio_on)
            {
                Mix_PlayChannel(-1, Game_Audio[GAME_OOPS], 0);
            }
            game->status = GAME_OVER;
        }

        render_game_play(game);
    }
}

void update_game_pause(Game* game)
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gRenderer);
    
    Game_Pause_Background.render(0, 0, gRenderer);

    Home_Icon.free();

    Music.free();
    Audio.free();

    Resume.set_button_without_texture(420, 169, 260, 47);

    Home_Icon.set_button_without_texture(511, 418, 80, 80);

    Play_Again.set_button_without_texture(385, 364, 333, 47);

    if(Resume.be_clicked())
    {
        game->status = GAME_PLAY;
    }

    if(Home_Icon.be_clicked())
    {
        game->status = GAME_ON_MENU;
    }

    if(Play_Again.be_clicked())
    {
        game->reset();
        game->status = GAME_PLAY;
    }

    if(Music.be_clicked())
    {
        if(game->music_on)
        {
            game->music_on = false;
        }
        else
        {
            game->music_on = true;
        }
    }

    switch(game->music_on)
    {
    case true:
        Music.set_up(Button_Path[MUSIC_ON], 398, 224, gRenderer);
        break;
    case false:
        Music.set_up(Button_Path[MUSIC_OFF], 398, 224, gRenderer);
        break;
    }
    
    if(Audio.be_clicked())
    {
        if(game->audio_on)
        {
            game->audio_on = false;
        }
        else
        {
            game->audio_on = true;
        }
    }

    switch(game->audio_on)
    {
    case true:
        Audio.set_up(Button_Path[AUDIO_ON], 398, 295, gRenderer);
        break;
    case false:
        Audio.set_up(Button_Path[AUDIO_OFF], 398, 295, gRenderer);
        break;
    }

    Resume.update_button_status();
    Home_Icon.update_button_status();
    Music.update_button_status();
    Audio.update_button_status();
    Play_Again.update_button_status();

    Music.render(gRenderer);
    Audio.render(gRenderer);

    SDL_RenderPresent(gRenderer);
}

void update_game_line(Game *game)
{
    if(game->real_time >= game->highlight_end_time)
    {
        game->empty_rows_filled();
        if(game->audio_on)
        {
            Mix_PlayChannel(-1, Game_Audio[LINE_CLEAR], 0);
        }
        game->cleared_lines_count += game->current_cleared_lines;

        //if (game->cleared_lines_count >= game->get_lines_for_next_level() && game->level < 29) game->level++;

        game->point += game->calculate_game_point();
        game->status = GAME_PLAY;
    }
}

void update_game_over(Game *game, Game_input *input)
{
    long long int current_point = game->point;

    if(game->real_time > game->before_end_time)
    {
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderClear(gRenderer);
        
        Game_Over.render(0, 0, gRenderer);

        End_Game_Score.loadFromRenderedText(std::to_string(current_point), white, gRenderer, gFont);
        End_Game_Score.render( (SCREEN_WIDTH * BLOCK_SIZE - End_Game_Score.getWidth()) / 2, (SCREEN_HEIGHT * BLOCK_SIZE) * 0.71, gRenderer);

        Home_Icon.free();
        Play_Again.free();

        Home_Icon.set_up(Button_Path[HOME_ICON], 310, 150, gRenderer);
        Play_Again.set_up(Button_Path[PLAY_AGAIN], 709, 150, gRenderer);

        Home_Icon.render(gRenderer);
        Play_Again.render(gRenderer);

        SDL_RenderPresent(gRenderer);
    }

    if(Home_Icon.be_clicked())
    {
        game->status = GAME_ON_MENU;
    }

    if(Play_Again.be_clicked())
    {
        game->reset();
        game->status = GAME_PLAY;
    }

    Home_Icon.update_button_status();
    Play_Again.update_button_status();
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

void handle_button(Game* game, SDL_Event* e)
{
    if(game->status == GAME_ON_MENU)
    {
        Play.handleEvent(e);
        Setting.handleEvent(e);
        Quit.handleEvent(e);
    }

    if(game->status == GAME_ON_SETTING)
    {
        Level_Button.handleEvent(e);
        Music.handleEvent(e);
        Audio.handleEvent(e);
        Home_Icon.handleEvent(e);
    }

    if(game->status == GAME_ON_PAUSE)
    {
        Resume.handleEvent(e);
        Music.handleEvent(e);
        Audio.handleEvent(e);
        Home_Icon.handleEvent(e);
        Play_Again.handleEvent(e);
    }

    if(game->status == GAME_PLAY)
    {
        Pause_Icon.handleEvent(e);
    }

    if(game->status == GAME_OVER)
    {
        Home_Icon.handleEvent(e);
        Play_Again.handleEvent(e);
    }
}

void setting_button_set_up(Game* game)
{
    if(Level_Button.be_clicked())
    {
        game->start_level = (game->start_level + 1) % 3;
    }
    
    switch(game->start_level)
    {
    case 0:
        Level_Button.set_up(Button_Path[LEVEL_1], 420, 169, gRenderer);
        break;
    
    case 1:
        Level_Button.set_up(Button_Path[LEVEL_2], 420, 169, gRenderer);
        break;

    case 2:
        Level_Button.set_up(Button_Path[LEVEL_3], 420, 169, gRenderer);
        break;
    }

    Music.free();
    Audio.free();

    if(Music.be_clicked())
    {
        if(game->music_on)
        {
            game->music_on = false;
        }
        else
        {
            game->music_on = true;
        }
    }

    switch(game->music_on)
    {
    case true:
        Music.set_up(Button_Path[MUSIC_ON], 398, 248, gRenderer);
        break;
    case false:
        Music.set_up(Button_Path[MUSIC_OFF], 398, 248, gRenderer);
        break;
    }
    
    if(Audio.be_clicked())
    {
        if(game->audio_on)
        {
            game->audio_on = false;
        }
        else
        {
            game->audio_on = true;
        }
    }

    switch(game->audio_on)
    {
    case true:
        Audio.set_up(Button_Path[AUDIO_ON], 398, 323, gRenderer);
        break;
    case false:
        Audio.set_up(Button_Path[AUDIO_OFF], 398, 323, gRenderer);
        break;
    }

    Home_Icon.free();

    Home_Icon.set_up(Button_Path[HOME_ICON], 510, 396, gRenderer);

    if(Home_Icon.be_clicked())
    {
        game->status = GAME_ON_MENU;
    }

    Level_Button.update_button_status();
    Music.update_button_status();
    Audio.update_button_status();
    Home_Icon.update_button_status();

}

//Render____________________________________________________________________________________________________________

void render_game_play(Game* game)
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gRenderer);

    render_background();

    render_board(game);

    draw_next_piece(game);

    draw_hold_piece(game);

    draw_piece(&game->piece);

    render_string_objects(game);

    Pause_Icon.render(gRenderer);

    SDL_RenderPresent(gRenderer);
}

void render_background()
{
    Background.render(0, 0, gRenderer);
    Main_Board.render( (SCREEN_WIDTH * BLOCK_SIZE - BOARD_WIDTH * BLOCK_SIZE) / 2, (SCREEN_HEIGHT * BLOCK_SIZE - VISIBLE_HEIGHT * BLOCK_SIZE) / 2, gRenderer);

    Next_Piece.render( (SCREEN_WIDTH * BLOCK_SIZE - BOARD_WIDTH * BLOCK_SIZE) / 2 + BLOCK_SIZE * 14, (SCREEN_HEIGHT * BLOCK_SIZE - VISIBLE_HEIGHT * BLOCK_SIZE) / 2, gRenderer);
    Hold_Piece.render( (SCREEN_WIDTH * BLOCK_SIZE - BOARD_WIDTH * BLOCK_SIZE) / 2 + BLOCK_SIZE * 14, (SCREEN_HEIGHT * BLOCK_SIZE - VISIBLE_HEIGHT * BLOCK_SIZE) / 2 + BLOCK_SIZE * 12, gRenderer);
    
    Score_And_Level_Board.render( (SCREEN_WIDTH * BLOCK_SIZE - BOARD_WIDTH * BLOCK_SIZE) / 2 - BLOCK_SIZE * 10, (SCREEN_HEIGHT * BLOCK_SIZE - VISIBLE_HEIGHT * BLOCK_SIZE) / 2, gRenderer);
    Record_Board.render( (SCREEN_WIDTH * BLOCK_SIZE - BOARD_WIDTH * BLOCK_SIZE) / 2 - BLOCK_SIZE * 10, (SCREEN_HEIGHT * BLOCK_SIZE - VISIBLE_HEIGHT * BLOCK_SIZE) / 2 + BLOCK_SIZE * 12, gRenderer);
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

void render_string_objects(Game *game)
{
    //Render text
    SDL_Color white = { 255, 255, 255 };

    int level_render = game->start_level + 1;
    
    if( !Level.loadFromRenderedText( std::to_string(level_render), white, gRenderer, gFont ) )
    {
        printf( "Failed to render level texture!\n" );
    }
    else
    {
        int x = (SCREEN_WIDTH * BLOCK_SIZE - BOARD_WIDTH * BLOCK_SIZE) / 2 - BLOCK_SIZE * 10;
        int y = (SCREEN_HEIGHT * BLOCK_SIZE - VISIBLE_HEIGHT * BLOCK_SIZE) / 2;

        Level.render( x + (150 - Level.getWidth()) / 2, y + (200 - Level.getHeight()) / 4, gRenderer);
    }

    if( !Score.loadFromRenderedText( std::to_string(game->point), white, gRenderer, gFont ) )
    {
        printf( "Failed to render score texture!\n" );
    }
    else
    {
        int x1 = (SCREEN_WIDTH * BLOCK_SIZE - BOARD_WIDTH * BLOCK_SIZE) / 2 - BLOCK_SIZE * 10;
        int y1 = (SCREEN_HEIGHT * BLOCK_SIZE - VISIBLE_HEIGHT * BLOCK_SIZE) / 2;

        Score.render( x1 + (150 - Score.getWidth()) / 2, y1 + (200 - Score.getHeight()) * 0.8, gRenderer);
    }

    if( !Record.loadFromRenderedText( std::to_string(game->record_point), white, gRenderer, gFont ) )
    {
        printf( "Failed to render record texture!\n" );
    }
    else
    {
        int x2 = (SCREEN_WIDTH * BLOCK_SIZE - BOARD_WIDTH * BLOCK_SIZE) / 2 - BLOCK_SIZE * 10;
        int y2 = (SCREEN_HEIGHT * BLOCK_SIZE - VISIBLE_HEIGHT * BLOCK_SIZE) / 2 + BLOCK_SIZE * 12;

        Record.render( x2 + (150 - Record.getWidth()) / 2, y2 + (200 - Record.getHeight()) / 2, gRenderer);
    }
    
}


int main(int argc, char* args[])
{
    
    Game game = {};

    //game.spawn_new_piece();

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


            while(!game.game_quit)
            {
                while(SDL_PollEvent(&e) != 0)
                {
                    if(e.type == SDL_QUIT)
                    {
                        game.game_quit = true;
                    }

                    handle_button(&game, &e);
                }

                game.real_time = SDL_GetTicks() / 1000.0f;

                //handle_keyboard(&input);

                update_game(&game, &input);

            }
        }

    }

    close();

    return 0;
}
