#ifndef _BOARD_
#define _BOARD_

#include "Common.h"
#include "Pieces.h"

//BOARD AND PIECE VALUE
#define BLOCK_SIZE 16
#define BOARD_XPOS 560 //position from the left of the screen
#define BOARD_YPOS 160 //position from top of the screen
#define BOARD_WIDTH 10 //in blocks
#define BOARD_HEIGHT 20 //in blocks
#define BOARD_LIMIT 30 //distance of top edge and bottom edge with the board
#define PIECE_BLOCKS 5

class Board
{
public:

	Board						(Pieces *pPieces, int pScreenHeight);

	int GetXPosInPixels			(int pPos);
	int GetYPosInPixels			(int pPos);
	bool IsFreeBlock			(int pX, int pY);
	bool IsPossibleMovement		(int pX, int pY, int pPiece, int pRotation);
	void StorePiece				(int pX, int pY, int pPiece, int pRotation);
	void DeletePossibleLines	();
	bool IsGameOver				();

private:

	enum { POS_FREE, POS_FILLED };			// POS_FREE = free position of the board; POS_FILLED = filled position of the board
	int mBoard [BOARD_WIDTH][BOARD_HEIGHT];	// Board that contains the pieces
	Pieces *mPieces;
	int mScreenHeight;

	void InitBoard();
	void DeleteLine (int pY);
};

#endif