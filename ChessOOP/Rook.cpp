#include "Rook.h"

Rook::Rook(int colour) : Piece(colour) {};

char Rook::getSymbol() const {
    return colour == 1 ? 'R' : 'r';
}
