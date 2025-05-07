#include <iostream>
#include "Bishop.h"


Bishop::Bishop(int colour) : Piece(colour) {}

char Bishop::getSymbol() const {
    return colour == 1 ? 'B' : 'b';
}
