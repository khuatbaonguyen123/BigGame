#ifndef _COMMON_
#define _COMMON_

#include <iostream>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BBP = 32;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
TTF_Font *gFont = NULL;

//Piece Texture
SDL_Texture* pieceTexture = NULL;

//Board Texture
SDL_Texture* boardTexture = NULL;

//Background texture
SDL_Texture* bkgTexture = NULL;

//Holding next piece board
SDL_Texture* nextPieceBoard = NULL;

//COLOR KEY
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

#endif