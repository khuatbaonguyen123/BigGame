#ifndef COMMON_H
#define COMMON_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

#include "Piece.h"

const int SCREEN_WIDTH = 1100;
const int SCREEN_HEIGHT = 625;

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 22;

const int VISIBLE_HEIGHT = 20;
const int BLOCK_SIZE = 25;

//convert one dimensional array to matrix


int get_data_value(const int* values, const int width, const int row, const int col);
void set_data_value(int* values, const int width, const int row, const int col, const int value);


enum GAME_STATUS
{
        GAME_PLAY
};


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

        int left_status = 0;
        int right_status = 0;
        int down_status = 0;
        int up_status = 0;
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

const std::string Block_Paths[7] =
{
    "Images/Blue.png",
    "Images/Green.png",
    "Images/LightBlue.png",
    "Images/Orange.png",
    "Images/Purple.png",
    "Images/Red.png",
    "Images/Yellow.png"
};

const std::string Background_Path = "Images/Background.png";

const std::string Main_Board_Path = "Images/Board.png";

#endif