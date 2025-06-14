#include "Rook.h"
#include <cmath>
#include "Board.h"
Rook::Rook(Colour colour) : Piece(colour, Type::ROOK) {};

wchar_t Rook::getSymbol() const {
	return colour == Colour::WHITE ? L'♖' : L'♜';
}

Piece* Rook::clone() const {
    return new Rook(colour);
}

bool Rook::isValidMove(int fromRow, int fromCol, int toRow, int toCol, const Board& board) const {
    // Must move in straight line (same row or same column)
    if (fromRow != toRow && fromCol != toCol) {
        return false;
    }

    // Check if target square has friendly piece
    Piece* target = board.get(toRow, toCol);
    if (target && target->getColor() == colour) {
        return false;
    }

    // Check path is clear
    int rowDir = (toRow > fromRow) ? 1 : (toRow < fromRow) ? -1 : 0;
    int colDir = (toCol > fromCol) ? 1 : (toCol < fromCol) ? -1 : 0;

    int currentRow = fromRow + rowDir;
    int currentCol = fromCol + colDir;

    while (currentRow != toRow || currentCol != toCol) {
        if (board.get(currentRow, currentCol)) {
            return false; // Path blocked
        }
        currentRow += rowDir;
        currentCol += colDir;
    }

    return true;
}

