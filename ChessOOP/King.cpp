#include "King.h"

King::King(int colour) : Piece(colour) {};

char King::getSymbol() const {
    return colour == 1 ? 'K' : 'k';
}
