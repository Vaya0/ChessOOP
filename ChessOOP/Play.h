#pragma once
#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
class Play
{
public:
	Board board;
	char gameField[18][9];//we will write the figuers as letters for now
							//we need 9 rows for the white POV and 9 rows below for the black POV
	Play();
	~Play();
	void startGame();
	bool isKingDead = false;

private:

};

