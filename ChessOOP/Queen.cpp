#include "Queen.h"
#include <cmath>
#include "Board.h"
Queen::Queen(Colour colour) : Piece(colour, Type::QUEEN) {};

wchar_t Queen::getSymbol() const  {
    return colour == Colour::WHITE ? L'♕' : L'♛';
}
Piece* Queen::clone() const {
    return new Queen(colour);
}
bool Queen::isValidMove(int fromRow, int fromCol, int toRow, int toCol, const Board& board) const {
    // Queen moves like rook or bishop
    bool isRookMove = (fromRow == toRow || fromCol == toCol);
    bool isBishopMove = (abs(toRow - fromRow) == abs(toCol - fromCol));

    if (!isRookMove && !isBishopMove) {
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

