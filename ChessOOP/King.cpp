#include "King.h"
#include <cmath>
#include "Board.h"
King::King(Colour colour) : Piece(colour, Type::KING) {};

wchar_t King::getSymbol() const {
    return colour == Colour::WHITE ? L'♔' : L'♚';
}
Piece* King::clone() const {
    return new King(colour);
}

bool King::isValidMove(int fromRow, int fromCol, int toRow, int toCol, const Board& board) const {
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);

    // King moves one square in any direction (or castling - handled separately)
    if (rowDiff > 1 || colDiff > 1) {
        // Check for castling (2 squares horizontally)
        if (rowDiff == 0 && colDiff == 2) {
            return true; // Castling validation handled in Game class
        }
        return false;
    }

    // Check if target square has friendly piece
    Piece* target = board.get(toRow, toCol);
    if (target && target->getColor() == colour) {
        return false;
    }

    return true;
}

