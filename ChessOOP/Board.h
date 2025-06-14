#pragma once
#include "Piece.h"

//class Piece;

class Board
{
public:
	Board();
	~Board();
	void initializeBoard();
	Piece* get(int row, int col) const;
	void set(int row, int col, Piece* piece);
	void set(int torow, int tocol, Piece* piece, int fromrow, int fromcol);
	Board(const Board& other);
	Board& operator=(const Board& other);
	Board(Board&& other) noexcept;
	Board& operator=(Board&& other) noexcept;
private:
	Piece* board[8][8];//num of squares on board
	void free();
};
