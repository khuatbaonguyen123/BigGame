//
// Created by My PC on 01/05/2022.
//

#ifndef COMMON_H
#define COMMON_H


#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <time.h>

//files
#include "Tetrimino.h"

#define SCREEN_WIDTH 44
#define SCREEN_HEIGHT 25
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 22

#define VISIBLE_HEIGHT 20
#define BLOCK_SIZE 25

//some colors
const SDL_Color white = {255,255,255,255};
const SDL_Color black = {0,0,0,255};


//time to the next drop for each level
const double DROP_FRAMES_PER_LEVEL[] = {
        48,
        43,
        38,
        33,
        28,
        23,
        18,
        13,
        8,
        6,
        5,5,5,
        4,4,4,
        3,3,3,
        2,2,2,2,2,2,2,2,2,2,
        1
};

//status of the game
enum GAME_STATUS  
{
        GAME_ON_MENU,
        GAME_PLAY,
        GAME_HIGHLIGHT_LINE,
        GAME_OVER
};

enum GAME_AUDIO
{
        DROP,
        HARD_DROP,
        LINE_CLEAR,
        MOVE,
        ROTATE,
        GAME_OOPS
};

//input class for handling keyboard
class Game_input {
public:
    int left;
    int right;
    int up;
    int down;
    int enter;
    int space;

    int S_key;

    //while the value of status is greater than 0, it means they are pressed
    int left_status;
    int right_status;
    int down_status;
    int up_status;
    int enter_status;
    int space_status;

    int S_key_status;

    //constructor
    Game_input()
    {
        left = 0;
        right = 0;
        up = 0;
        down = 0;
        enter = 0;
        space = 0;

        S_key = 0;

        left_status = 0;
        right_status = 0;
        down_status = 0;
        up_status = 0;  
        enter_status = 0;
        space_status = 0;

        S_key_status = 0;
    }
};

//piece matrix
const int TETRIMINO_1[] = {
        0,0,0,0,
        1,1,1,1,
        0,0,0,0,
        0,0,0,0
};

const int TETRIMINO_2[] = {
        2,2,
        2,2
};

const int TETRIMINO_3[] = {
        0,0,0,
        3,3,3,
        0,3,0,
};

const int TETRIMINO_4[] = {
        0,4,4,
        4,4,0,
        0,0,0
};

const int TETRIMINO_5[] = {
        5,5,0,
        0,5,5,
        0,0,0
};

const int TETRIMINO_6[] = {
        6,0,0,
        6,6,6,
        0,0,0
};

const int TETRIMINO_7[] = {
        0,0,7,
        7,7,7,
        0,0,0
};


//Tetrimino includes matrix of the piece and the side of it
Tetrimino tetrimino(const int *data, const int&side);
const Tetrimino TETRIMINOS[] = {
        tetrimino(TETRIMINO_1,4),
        tetrimino(TETRIMINO_2,2),
        tetrimino(TETRIMINO_3,3),
        tetrimino(TETRIMINO_4,3),
        tetrimino(TETRIMINO_5,3),
        tetrimino(TETRIMINO_6,3),
        tetrimino(TETRIMINO_7,3),
};


/***
    blocks' path:
    - These string paths are used to render the blocks in board game.
    - These string are about the path to images
 ***/
const std::string Block_Path[7] = {
        "Images/LightBlue.png",
        "Images/Yellow.png",
        "Images/Purple.png",
        "Images/Green.png",
        "Images/Red.png",
        "Images/Blue.png",
        "Images/Orange.png"
};

const std::string Piece_Path[7] = {
        "Images/I.png",
        "Images/O.png",
        "Images/T.png",
        "Images/S.png",
        "Images/Z.png",
        "Images/J.png",
        "Images/L.png"      
};

const std::string Background_Path = "Images/Background.png";

const std::string Main_Board_Path = "Images/Board.png";

const std::string Next_Piece_Path = "Images/Next_Piece.png";

const std::string Hold_Piece_Path = "Images/Hold_Piece.png";

const std::string Score_And_Level_Path = "Images/Score_And_Level.png";

const std::string Game_Over_Path = "Images/Over.png";

const std::string Setting_Icon_Path = "Images/Setting_Icon.png";

const std::string Record_Board_Path = "Images/Record.png";

const std::string Game_Music_Path = "Music/Believer.mp3";

const std::string Game_Audio_Path[6] =
{
        "Music/SDL_Game_audio_Drop.wav",
        "Music/SDL_Game_audio_hardDrop.wav",
        "Music/SDL_Game_audio_Lineclear.wav",
        "Music/SDL_Game_audio_Move.wav",
        "Music/SDL_Game_audio_Rotate.wav",
        "Music/SDL_Game_audio_Gameover.wav"
};


/***
     Some funtion related to handle matrix because instead of using 2 dimensions matrix,
     program uses 1 dimensions and need some functions to present it like 2 dimensions matrix

    `get_date_value(...): get the element's value of the matrix
     set_date_value(...): set the element's value of the matrix
     get_date_value(...): copy matrix to another matrix
***/
int get_data_value(int *data, const int &width,
                    const int &row, const int&col);
void set_data_value(int *data, const int &width,
                    const int &row, const int &col ,const int &value );
void copyMatrix(int *matrix, int *copyMatrix, int height, int width);

int max(int x, int y);

int min(int x, int y);


/***
    Basic function to get a random number from the limitation is given
***/
int get_random_number(const int &min, const int &max);

#endif //COMMON_H


