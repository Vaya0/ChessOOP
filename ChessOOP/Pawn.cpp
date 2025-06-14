#include "Pawn.h"
#include <cmath>
#include "Board.h"
Pawn::Pawn(Colour colour) : Piece(colour, Type::PAWN) {};

wchar_t Pawn::getSymbol() const {
    return colour == Colour::WHITE ? L'♙' : L'♟';
}

Piece* Pawn::clone() const {
    return new Pawn(colour);
}

bool Pawn::isValidMove(int fromRow, int fromCol, int toRow, int toCol, const Board& board) const {
    int direction = (colour == Colour::WHITE) ? -1 : 1;
    int startRow = (colour == Colour::WHITE) ? 6 : 1;

    // Forward move
    if (fromCol == toCol) {
        // One square forward
        if (toRow == fromRow + direction && !board.get(toRow, toCol)) {
            return true;
        }
        // Two squares forward from starting position
        if (fromRow == startRow && toRow == fromRow + 2 * direction &&
            !board.get(toRow, toCol) && !board.get(fromRow + direction, toCol)) {
            return true;
        }
    }
    // Diagonal capture
    else if (std::abs(fromCol - toCol) == 1 && toRow == fromRow + direction) {
        Piece* target = board.get(toRow, toCol);
        if (!target || target->getColor() != colour) {
            return true;
        }
    }

    return false;
}
