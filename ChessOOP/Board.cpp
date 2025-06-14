#include "Board.h"
#include "PieceFactory.h"

Board::Board() {
	initializeBoard();
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

	for (int i = 0; i < 8; ++i) {
		board[1][i] = PieceFactory::createFigure(Colour::BLACK, Type::PAWN);
		board[6][i] = PieceFactory::createFigure(Colour::WHITE, Type::PAWN);
	}

	board[0][0] = PieceFactory::createFigure(Colour::BLACK, Type::ROOK);
	board[0][7] = PieceFactory::createFigure(Colour::BLACK, Type::ROOK);
	board[7][0] = PieceFactory::createFigure(Colour::WHITE, Type::ROOK);
	board[7][7] = PieceFactory::createFigure(Colour::WHITE, Type::ROOK);

	board[0][1] = PieceFactory::createFigure(Colour::BLACK, Type::KNIGHT);
	board[0][6] = PieceFactory::createFigure(Colour::BLACK, Type::KNIGHT);
	board[7][1] = PieceFactory::createFigure(Colour::WHITE, Type::KNIGHT);
	board[7][6] = PieceFactory::createFigure(Colour::WHITE, Type::KNIGHT);

	board[0][2] = PieceFactory::createFigure(Colour::BLACK, Type::BISHOP);
	board[0][5] = PieceFactory::createFigure(Colour::BLACK, Type::BISHOP);
	board[7][2] = PieceFactory::createFigure(Colour::WHITE, Type::BISHOP);
	board[7][5] = PieceFactory::createFigure(Colour::WHITE, Type::BISHOP);

	board[0][3] = PieceFactory::createFigure(Colour::BLACK, Type::QUEEN);
	board[7][3] = PieceFactory::createFigure(Colour::WHITE, Type::QUEEN);

	board[0][4] = PieceFactory::createFigure(Colour::BLACK, Type::KING);
	board[7][4] = PieceFactory::createFigure(Colour::WHITE, Type::KING);
}

Piece* Board::get(int row, int col) const {
	// Add bounds checking
	if (row < 0 || row >= 8 || col < 0 || col >= 8) {
		return nullptr;
	}
	return board[row][col];
}

void Board::set(int row, int col, Piece* piece) {
	if (row < 0 || row >= 8 || col < 0 || col >= 8) return;  // bounds check

	if (board[row][col] != piece) {  // Avoid deleting the same piece we're setting
		delete board[row][col];
		
	}
	board[row][col] = piece;
	
}

void Board::set(int torow, int tocol, Piece* piece, int fromrow, int fromcol) {
	if (torow < 0 || torow >= 8 || tocol < 0 || tocol >= 8) return;  // bounds check

	if (board[torow][tocol] != piece) {  // Avoid deleting the same piece we're setting
		delete board[torow][tocol];
		board[torow][tocol] = piece;
		board[fromrow][fromcol] = nullptr;
	}
	
}

Board::Board(const Board& other) {
	for (int row = 0; row < 8; ++row)
		for (int col = 0; col < 8; ++col)
			board[row][col] = nullptr;

	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			if (other.board[row][col] != nullptr) {
				board[row][col] = other.board[row][col]->clone();
			}
		}
	}
}

Board& Board::operator=(const Board& other) {
	if (this != &other) {  
		free();

		for (int row = 0; row < 8; ++row) {
			for (int col = 0; col < 8; ++col) {
				if (other.board[row][col] != nullptr) {
					board[row][col] = other.board[row][col]->clone();
				}
				else {
					board[row][col] = nullptr;
				}
			}
		}
	}
	return *this;
}

Board::Board(Board&& other) noexcept {
	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			board[row][col] = other.board[row][col];
			other.board[row][col] = nullptr; 
		}
	}
}

Board& Board::operator=(Board&& other) noexcept {
	if (this != &other) {  
		free();

		for (int row = 0; row < 8; ++row) {
			for (int col = 0; col < 8; ++col) {
				board[row][col] = other.board[row][col];
				other.board[row][col] = nullptr; 
			}
		}
	}
	return *this;
}