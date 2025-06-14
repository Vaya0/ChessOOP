#include "Knight.h"
#include <cmath>
#include "Board.h"
Knight::Knight(Colour colour) : Piece(colour,Type::KNIGHT) {};

wchar_t Knight::getSymbol() const {
	return colour == Colour::WHITE ? L'♘' : L'♞';
}
Piece* Knight::clone() const {
    return new Knight(colour);
}
bool Knight::isValidMove(int fromRow, int fromCol, int toRow, int toCol, const Board& board) const {
    int rowDiff = std::abs(toRow - fromRow);
    int colDiff = std::abs(toCol - fromCol);

    // Knight moves in L-shape: 2+1 or 1+2
    if (!((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2))) {
        return false;
    }

    // Check if target square has friendly piece
    Piece* target = board.get(toRow, toCol);
    if (target && target->getColor() == colour) {
        return false;
    }

    return true;
}
