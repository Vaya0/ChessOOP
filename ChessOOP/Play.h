#pragma once
#include <iostream>
#include "String.h"
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
	int player = 2;
	bool isKingDead = false;

	void startGame();
	bool isMoveCommandValid(String move);
	bool canMove(const String& move, Board& board, int currentPlayer);
	void FillBoard();
	void PaintBoard();
	void PrintBorders();
	void PrintNumbering();
	void FigureSpaceCleaning();
	void PlacePieces(Board board);
	void PrintBoard(Board board);

private:
	
};

