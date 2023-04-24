#include "Game.h"

//Init
Game::Game(Board *pBoard, Pieces *pPieces, LTexture *pTexture)
{
    //Get the pointer to the board and pieces
    mBoard = pBoard;
    mPieces = pPieces;
	mTexture = pTexture;

    InitGame();
}

//Get a random num between 2 numbers
int Game::GetRand(int pA, int pB)
{
    return rand () % (pB - pA + 1) + pA;
}

void Game::InitGame()
{
	// Init random numbers
	srand ((unsigned int) time(NULL));

	// First piece
	mPiece	= GetRand (0, 6);
	mRotation = GetRand (0, 3);
	mPosX = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition (mPiece, mRotation);
	mPosY = mPieces->GetYInitialPosition (mPiece, mRotation);

	//  Next piece
	mNextPiece 	= GetRand (0, 6);
	mNextRotation = GetRand (0, 3);
	mNextPosX = BOARD_WIDTH + 5;
	mNextPosY = 5;	
}

//Random new piece
void Game::CreateNewPiece()
{
    //Set up the current piece
    mPiece = mNextPiece;
    mRotation = mNextRotation;
	mPosX = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition (mPiece, mRotation);
	mPosY = mPieces->GetYInitialPosition (mPiece, mRotation);

    //Random the next piece
    mNextPiece = GetRand(0, 6);
    mNextRotation = GetRand(0, 3);
    
}

void Game::DrawPiece (int pX, int pY, int pPiece, int pRotation)
{
    int posX = mBoard->GetXPosInPixels(pX);
    int posY = mBoard->GetYPosInPixels(pY);

	for (int i = 0; i < PIECE_BLOCKS; i++)
	{
		for (int j = 0; j < PIECE_BLOCKS; j++)
		{
			// Get the type of the block and draw it with the correct color
			
			if (mPieces->GetBlockType (pPiece, pRotation, j, i) != 0){
				SDL_Rect DrawPiece = {posX, posY, BLOCK_SIZE, BLOCK_SIZE};
				switch(pPiece){
					case 0: SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255); break;
					case 1: SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255); break;
					case 2: SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, 255); break;
					case 3: SDL_SetRenderDrawColor(gRenderer, 0, 255, 255, 255); break;
					case 4: SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255); break;
					case 5: SDL_SetRenderDrawColor(gRenderer, 255, 128, 0, 255); break;
					case 6: SDL_SetRenderDrawColor(gRenderer, 255, 0, 255, 255); break;
				}
				SDL_RenderFillRect( gRenderer, &DrawPiece );

				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(gRenderer, &DrawPiece);
			}
		}
	}    
}

void Game::DrawBoard(SDL_Texture* boardTexture)
{
	SDL_Rect mainBoard = {BOARD_XPOS, BOARD_YPOS, BOARD_WIDTH * BLOCK_SIZE, BOARD_HEIGHT * BLOCK_SIZE};
	SDL_RenderCopy(gRenderer, boardTexture, NULL, &mainBoard);
}
