#include <iostream>
#include "Bishop.h"
#include <cmath>
#include "Board.h"


Bishop::Bishop(Colour colour) : Piece(colour, Type::BISHOP) {}

wchar_t Bishop::getSymbol() const { return colour == Colour::WHITE ? L'♗' : L'♝'; }

Piece* Bishop::clone() const {
    return new Bishop(colour);
}

bool Bishop::isValidMove(int fromRow, int fromCol, int toRow, int toCol, const Board& board) const {
    // Must move diagonally
    if (abs(toRow - fromRow) != abs(toCol - fromCol)) {
        return false;
    }

    // Check if target square has friendly piece
    Piece* target = board.get(toRow, toCol);
    if (target && target->getColor() == colour) {
        return false;
    }

    // Check path is clear
    int rowDir = (toRow > fromRow) ? 1 : -1;
    int colDir = (toCol > fromCol) ? 1 : -1;

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

