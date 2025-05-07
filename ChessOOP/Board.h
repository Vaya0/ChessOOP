#pragma once
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

class Board
{
public:
	void initializeBoard();
private:
	Piece field[8][8];//num of squares on board
};

//if a square is empty we have the default piece without a name in it