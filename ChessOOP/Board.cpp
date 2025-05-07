#include "Board.h"

Board::Board() {
	//initialize all squares to nullptr
	for (int row = 0; row < 8; ++row)
		for (int col = 0; col < 8; ++col)
			board[row][col] = nullptr;
}
Board::~Board() {
	free();
}

void Board::free() {
    for (int row = 0; row < 8; ++row)
        for (int col = 0; col < 8; ++col) {
            delete board[row][col];
            board[row][col] = nullptr;
        }
}
void Board::initializeBoard() {

	free();

	// Example: place white and black pawns
	for (int i = 0; i < 8; ++i) {
		board[1][i] = new Pawn(2);
		board[6][i] = new Pawn(1);
	}

	// Example: place rooks
	board[0][0] = new Rook(2);
	board[0][7] = new Rook(2);
	board[7][0] = new Rook(1);
	board[7][7] = new Rook(1);
	// Example: place knights
	board[0][1] = new Knight(2);
	board[0][6] = new Knight(2);
	board[7][1] = new Knight(1);
	board[7][6] = new Knight(1);
	// Example: place bishops
	board[0][2] = new Bishop(2);
	board[0][5] = new Bishop(2);
	board[7][2] = new Bishop(1);
	board[7][5] = new Bishop(1);
	// Example: place queens
	board[0][3] = new Queen(2);
	board[7][3] = new Queen(1);
	// Example: place kings
	board[0][4] = new King(2);
	board[7][4] = new King(1);
}
