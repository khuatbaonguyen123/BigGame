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
#include <algorithm>
#include <sstream>

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
enum GAME_STATUS  {
        GAME_PLAY
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
        "Images/Orange.png",
        "Images/Blue.png"
};

const std::string Background_Path = "Images/Background.png";

const std::string Main_Board_Path = "Images/Board.png";


/***
     Some funtion related to handle matrix because instead of using 2 dimensions matrix,
     program uses 1 dimensions and need some functions to present it like 2 dimensions matrix

    `get_date_value(...): get the element's value of the matrix
     set_date_value(...): set the element's value of the matrix
     get_date_value(...): copy matrix to another matrix
***/
int get_data_value(const int *data, const int &width,
                    const int &row, const int&col);
void set_data_value(int *data, const int &width,
                    const int &row, const int &colm ,const int &value );


/***
    Basic function to get a random number from the limitation is given
***/
int get_random_number(const int &min, const int &max);

#endif //COMMON_H


