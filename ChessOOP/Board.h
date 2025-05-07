#pragma once
#include "Piece.h"

class Board
{
public:
	Board();
	~Board();
	void initializeBoard();
private:
	Piece* board[8][8];//num of squares on board
	void free();
	Piece* get(int row, int col) const;
	void set(int row, int col, Piece* piece);
};
